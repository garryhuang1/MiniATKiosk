#ifndef _KEYPAD_RENDER_H_
#define _KEYPAD_RENDER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Button;

extern bool loadButton();
extern bool init();
extern SDL_Surface* load_media();
extern void closeWindow();
extern void setPostion(int y, int x, int row, int col, int k);
extern void eventHandle(SDL_Event *e);

#endif /* KEYPAD_RENDER_H_ */