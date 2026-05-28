#ifndef SCREEN_H
#define SCREEN_H

void init_screen(void);
void term_screen(void);
void clear_screen(void);
void clear_palette(void);
void lock_screen(void);
void unlock_screen(void);
unsigned char* get_screen_pixels(void);
int get_scanline_padding(void);
void blit_screen(void);
void start_timer(void);

#endif
