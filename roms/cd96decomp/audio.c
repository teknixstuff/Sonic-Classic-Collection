#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opusfile.h>
#include "SDL.h"
#include "cmp.h"
#include "constants.h"
#include "pcminfo.h"
#include "soundchannel.h"
#include "util.h"
static void fill_audio_buffer(void* userdata, unsigned char* stream, int length);

extern int g_use_original_soundtrack;
static pcm_info g_sounds[AUDIO_SOUNDS] = { 0 };
static sound_channel g_channels[6] = { 0 };
static pcm_info g_music = { 0 };
static unsigned long g_musicOffset = -1;

void init_audio(void) {
  SDL_AudioSpec spec;

  if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
    fprintf(stderr, "SDL_InitSubSystem failed. Error: %s\n", SDL_GetError());
    abort();
  }
  spec.freq = 48000;
  spec.format = AUDIO_S16;
  spec.channels = 2;
  spec.samples = 512;
  spec.callback = fill_audio_buffer;
  spec.userdata = 0;
  if (SDL_OpenAudio(&spec, 0) != 0) {
    fprintf(stderr, "SDL_OpenAudio failed. Error: %s\n", SDL_GetError());
    abort();
  }
  stop_sounds();
}


void term_audio(void) {
  SDL_CloseAudio();
  SDL_QuitSubSystem(SDL_INIT_AUDIO);
}


void play_audio(void) {
  SDL_PauseAudio(0);
}

void play_bgm(short id) {
  SDL_LockAudio();
  if (g_music.size != 0) {
	  free(g_music.p_data);
	  g_music.size = 0;
  }
  static char soundtrack_path[sizeof("TITLE\\MUSIC\\BGM_??_00.OPUS")];
  if (id >= 36) {
	sprintf(soundtrack_path, "TITLE\\MUSIC\\BGM_%02i.OPUS", id);
  } else if (g_use_original_soundtrack) {
	sprintf(soundtrack_path, "TITLE\\MUSIC\\BGM_JP_%02i.OPUS", id);
  } else {
	sprintf(soundtrack_path, "TITLE\\MUSIC\\BGM_US_%02i.OPUS", id);
  }
  OggOpusFile* opusFile = op_open_file(soundtrack_path, NULL);
  if (!opusFile) {
	fprintf(stderr, "Could not open %s.\n", soundtrack_path);
    abort();
  }
  int sampleCount = op_pcm_total(opusFile, 0);
  g_music.size =  sampleCount * 2 * sizeof(opus_int16);
  g_music.p_data = malloc(g_music.size);
  int filled = 0;
  while (true) {
    int samples = op_read_stereo(opusFile, ((opus_int16*)g_music.p_data) + (filled * 2), (sampleCount - filled) * 2);
    if (samples < 0) {
	  fprintf(stderr, "Opus decode fault %i.\n", samples);
      abort();
    } else if (samples == 0) {
	  break;
	}
	filled += samples;
  }
  op_free(opusFile);
  g_musicOffset = 0;
  SDL_UnlockAudio();
}


void pause_bgm(void) {
  SDL_LockAudio();
  if (g_music.size != 0) {
      free(g_music.p_data);
      g_music.size = 0;
  }
  SDL_UnlockAudio();
}

long get_remaining_bgm(void) {
  return g_music.size - g_musicOffset;
}

void load_sounds(void) {
  cmp_header header;
  int i;
  FILE* fp = fopen("PCM.CMP", "rb");

  if (fp == 0) {
    fprintf(stderr, "Could not open PCM.CMP.\n");
    abort();
  }
  read_cmp_header_file(fp, &header);

  for (i = 0; i < AUDIO_SOUNDS; ++i) {
    read_ulong_littleendian_file(fp, &g_sounds[i].size);
  }

  for (i = 0; i < AUDIO_SOUNDS; ++i) {
    SDL_AudioCVT cvt;
    unsigned char* p_data = 0;

    if (SDL_BuildAudioCVT(&cvt, AUDIO_S16, 1, 22050, AUDIO_S16, 2, 48000) == -1) {
      fprintf(stderr, "SDL_BuildAudioCVT failed. Error: %s\n", SDL_GetError());
      abort();
    }
    p_data = malloc(g_sounds[i].size * cvt.len_mult);
    if (p_data == 0) {
      fprintf(stderr, "Could not allocate memory for audio sample conversion.\n");
      abort();
    }
    fread(p_data, 1, g_sounds[i].size, fp);
    cvt.buf = p_data;
    cvt.len = g_sounds[i].size;
    if (SDL_ConvertAudio(&cvt) == -1) {
      fprintf(stderr, "SDL_ConvertAudio failed. Error: %s\n", SDL_GetError());
      abort();
    }
    g_sounds[i].p_data = p_data;
    g_sounds[i].size = cvt.len_cvt;
  }
}


void unload_sounds(void) {
  int i;

  stop_sounds();

  for (i = 0; i < AUDIO_SOUNDS; ++i) {
    free(g_sounds[i].p_data);
  }
}


void play_sound(short id) {
  int i;

  SDL_LockAudio();

  for (i = 0; i < AUDIO_SOUND_CHANNELS; ++i) {
    if (g_channels[i].id == -1) {
      g_channels[i].id = id;
      g_channels[i].offset = 0;
      break;
    }
  }

  SDL_UnlockAudio();
}


void stop_sounds(void) {
  int i;

  SDL_LockAudio();

  for (i = 0; i < AUDIO_SOUND_CHANNELS; ++i) {
    g_channels[i].id = -1;
  }

  SDL_UnlockAudio();
}


static void fill_audio_buffer(void* userdata, unsigned char* stream, int length) {
  int i;

  memset(stream, 0, length);
  if (g_music.size != 0) {
	long remaining = g_music.size - g_musicOffset;
	if (length >= remaining) {
	  SDL_MixAudio(stream, g_music.p_data + g_musicOffset, remaining, SDL_MIX_MAXVOLUME);
	  SDL_MixAudio(stream + remaining, g_music.p_data, length - remaining, SDL_MIX_MAXVOLUME);
	  g_musicOffset = length - remaining;
	} else {
      SDL_MixAudio(stream, g_music.p_data + g_musicOffset, length, SDL_MIX_MAXVOLUME);
	  g_musicOffset += length;
	}
  }

  for (i = 0; i < AUDIO_SOUND_CHANNELS; ++i) {
    if (g_channels[i].id != -1) {
      pcm_info info = g_sounds[g_channels[i].id];
      long remaining = info.size - g_channels[i].offset;

      if (length >= remaining) {
        length = remaining;
        g_channels[i].id = -1;
      }
      SDL_MixAudio(stream, &info.p_data[g_channels[i].offset], length, SDL_MIX_MAXVOLUME);
      g_channels[i].offset += length;
    }
  }
}
