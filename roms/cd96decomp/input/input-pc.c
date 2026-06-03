#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "../GAME/EQU.h"

extern int g_quit;

static unsigned char g_buttons[8] = { 0 };
SDL_Joystick* gp_joystick = 0;


void init_input(void) {
  SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
  SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
  SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) != 0) {
    fprintf(stderr, "SDL_InitSubSystem failed. Error: %s\n", SDL_GetError());
    abort();
  }
  if (SDL_NumJoysticks() > 0) {
    SDL_JoystickEventState(SDL_ENABLE);
    gp_joystick = SDL_JoystickOpen(0);
  }
}


void term_input(void) {
  if (gp_joystick != 0) {
    SDL_JoystickClose(gp_joystick);
  }
  SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}


void poll_controller(void) {
  SDL_Event event;
  unsigned char buttons_down;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
        case SDLK_RIGHT: g_buttons[0] = 1; break;
        case SDLK_LEFT: g_buttons[1] = 1; break;
        case SDLK_DOWN: g_buttons[2] = 1; break;
        case SDLK_UP: g_buttons[3] = 1; break;
        case SDLK_x: g_buttons[4] = 1; break;
        case SDLK_z: g_buttons[5] = 1; break;
        case SDLK_a: g_buttons[6] = 1; break;
        case SDLK_RETURN: g_buttons[7] = 1; break;
      }
    }
    else if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
        case SDLK_RIGHT: g_buttons[0] = 0; break;
        case SDLK_LEFT: g_buttons[1] = 0; break;
        case SDLK_DOWN: g_buttons[2] = 0; break;
        case SDLK_UP: g_buttons[3] = 0; break;
        case SDLK_x: g_buttons[4] = 0; break;
        case SDLK_z: g_buttons[5] = 0; break;
        case SDLK_a: g_buttons[6] = 0; break;
        case SDLK_RETURN: g_buttons[7] = 0; break;
      }
    }
    else if (event.type == SDL_JOYAXISMOTION && event.jaxis.which == 0) {
      if (event.jaxis.axis == 0) {
        g_buttons[0] = event.jaxis.value > 8000;
        g_buttons[1] = event.jaxis.value < -8000;
      }
      else if (event.jaxis.axis == 1) {
        g_buttons[2] = event.jaxis.value > 8000;
        g_buttons[3] = event.jaxis.value < -8000;
      }
    }
    else if (event.type == SDL_JOYBUTTONDOWN) {
      switch (event.jbutton.button) {
        case 0: g_buttons[4] = 1; break;
        case 1: g_buttons[5] = 1; break;
        case 2: g_buttons[6] = 1; break;
        case 3: g_buttons[7] = 1; break;
      }
    }
    else if (event.type == SDL_JOYBUTTONUP) {
      switch (event.jbutton.button) {
        case 0: g_buttons[4] = 0; break;
        case 1: g_buttons[5] = 0; break;
        case 2: g_buttons[6] = 0; break;
        case 3: g_buttons[7] = 0; break;
      }
    }
    else if (event.type == SDL_QUIT) {
      g_quit = 1;
    }
  }

  swdata1.b.l = 0;
  if (g_buttons[0] != 0) {
    swdata1.b.l |= 0x08;
  }
  else if (g_buttons[1] != 0) {
    swdata1.b.l |= 0x04;
  }
  else if (g_buttons[2] != 0) {
    swdata1.b.l |= 0x02;
  }
  else if (g_buttons[3] != 0) {
    swdata1.b.l |= 0x01;
  }
  if (g_buttons[4] != 0) {
    swdata1.b.l |= 0x40;
  }
  if (g_buttons[5] != 0) {
    swdata1.b.l |= 0x10;
  }
  if (g_buttons[6] != 0) {
    swdata1.b.l |= 0x20;
  }
  if (g_buttons[7] != 0) {
    swdata1.b.l |= 0x80;
  }

  buttons_down = swdata1.b.h;
  buttons_down ^= swdata1.b.l;
  swdata1.b.h = swdata1.b.l;
  buttons_down &= swdata1.b.l;
  swdata1.b.l = buttons_down;
  swdata2.w = swdata1.w;
}
