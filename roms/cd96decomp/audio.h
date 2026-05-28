#ifndef AUDIO_H
#define AUDIO_H

void init_audio(void);
void term_audio(void);
void play_audio(void);
void play_bgm(short id);
void pause_bgm(void);
void load_sounds(void);
void unload_sounds(void);
void play_sound(short id);
void stop_sounds(void);
long get_remaining_bgm(void);

#endif
