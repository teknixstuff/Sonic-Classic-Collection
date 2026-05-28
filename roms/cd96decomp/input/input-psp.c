#include "input.h"
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "pspbutton.h"
#include "../GAME/EQU.h"


extern int g_quit;

static unsigned char g_buttons[8] = { 0 };
SDL_Joystick* gp_joystick = 0;


void init_input(void) {
  if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) != 0) {
    fprintf(stderr, "SDL_InitSubSystem failed. Error: %s\n", SDL_GetError());
    abort();
  }
  gp_joystick = SDL_JoystickOpen(0);
}


void term_input(void) {
  SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}


void poll_controller(void) {
  SDL_Event event;
  unsigned char buttons_down;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_JOYBUTTONDOWN) {
      switch (event.jbutton.button) {
        case PSP_BUTTON_RIGHT: g_buttons[0] = 1; break;
        case PSP_BUTTON_LEFT: g_buttons[1] = 1; break;
        case PSP_BUTTON_DOWN: g_buttons[2] = 1; break;
        case PSP_BUTTON_UP: g_buttons[3] = 1; break;
        case PSP_BUTTON_CROSS: g_buttons[4] = 1; break;
        case PSP_BUTTON_CIRCLE: g_buttons[5] = 1; break;
        case PSP_BUTTON_SQUARE: g_buttons[6] = 1; break;
        case PSP_BUTTON_START: g_buttons[7] = 1; break;
      }
    }
    else if (event.type == SDL_JOYBUTTONUP) {
      switch (event.jbutton.button) {
        case PSP_BUTTON_RIGHT: g_buttons[0] = 0; break;
        case PSP_BUTTON_LEFT: g_buttons[1] = 0; break;
        case PSP_BUTTON_DOWN: g_buttons[2] = 0; break;
        case PSP_BUTTON_UP: g_buttons[3] = 0; break;
        case PSP_BUTTON_CROSS: g_buttons[4] = 0; break;
        case PSP_BUTTON_CIRCLE: g_buttons[5] = 0; break;
        case PSP_BUTTON_SQUARE: g_buttons[6] = 0; break;
        case PSP_BUTTON_START: g_buttons[7] = 0; break;
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
