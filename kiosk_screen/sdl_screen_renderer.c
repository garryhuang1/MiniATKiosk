/*  sdl_screen_renderer.c
 *  Kiosk SDL Screen Rendering Implementation File
 *  Author: Aaron Hung
 *  Date: Feb. 28, 2015
 *  Purpose: To render the Kiosk screen by initializng SDL assets and applying them to an independent SDL window.
 *  Dependencies: SDL.h, SDL_image.h, stdbool.h, sdl-screen-1.00.h
 */

#include "sdl_screen_renderer.h"

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
 *  Function Prototypes
 */
int screen_init(int width, int height, const char* img_path);
bool SDL_init();
bool SDL_window_init(int width, int height);
bool SDL_window_surface_init();
bool SDL_load_screen_surface(const char* img_path);
bool SDL_apply_screen_surface(int x, int y, SDL_Surface* src, SDL_Surface* dest);
int screen_close();
void screen_renderer_error_handler(unsigned short error_code);

/*
 *  Error Code Constants
 */
const unsigned short SDL_INIT_ERROR = 0;
const unsigned short SDL_WINDOW_ERROR = 1;
const unsigned short SDL_WINDOW_SURFACE_ERROR = 2;
const unsigned short SDL_IMG_PATH_ERROR = 3;
const unsigned short SDL_IMG_OPTI_ERROR = 4;
const unsigned short SDL_IMG_LOAD_ERROR = 5;
const unsigned short SDL_SCREEN_BLIT_ERROR = 6;
const unsigned short SDL_WINDOW_SURFACE_UPDATE_ERROR = 7;
const unsigned short SDL_SCREEN_SURFACE_FREE_ERROR = 8;
const unsigned short SDL_WINDOW_FREE_ERROR = 9;

/*
 *  SDL Assets
 */
SDL_Window* window = NULL;
SDL_Surface* window_surface = NULL;
SDL_Surface* screen_surface = NULL;


int screen_init(int width, int height, const char* img_path) {
	bool success;

	success = SDL_init();

	if (!success) {
		screen_renderer_error_handler(SDL_INIT_ERROR);
	}

	if (success) {
		if (!SDL_window_init(width, height)) {
			success = false;
			screen_renderer_error_handler(SDL_WINDOW_ERROR);
		}
	}

	if (success) {
		if (!SDL_window_surface_init(window_surface)) {
			success = false;
			screen_renderer_error_handler(SDL_WINDOW_SURFACE_ERROR);
		}
	}

	if (success) {
		if (!SDL_load_screen_surface(img_path)) {
			success = false;
			screen_renderer_error_handler(SDL_IMG_LOAD_ERROR);
		}
	}

	if (success) {
		if (!SDL_apply_screen_surface(0,0,screen_surface, window_surface)) {
			success = false;
			screen_renderer_error_handler(SDL_SCREEN_BLIT_ERROR);
		}
	}

	if (success) {
		if (SDL_UpdateWindowSurface(window) < 0) {
			success = false;
			screen_renderer_error_handler(SDL_WINDOW_SURFACE_UPDATE_ERROR);
		}
	}

	if (success) {
		printf("Good!");
		return 1;
	} else {
		printf("Bad");
		return -1;
	}
}

bool SDL_init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}
	return true;
}

bool SDL_window_init(int width, int height) {
	window = SDL_CreateWindow("Kiosk-1.00", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		return false;
	}
	return true;
}

bool SDL_window_surface_init() {
	window_surface = SDL_GetWindowSurface(window);
	if (window_surface == NULL) {
		return false;
	}
	return true;
}

bool SDL_load_screen_surface(const char* img_path) {
	screen_surface = IMG_Load(img_path);

	if (screen_surface == NULL) {
		screen_renderer_error_handler(SDL_IMG_PATH_ERROR);
	}
	else {
		screen_surface = SDL_ConvertSurface(screen_surface, window_surface->format, NULL);
		if (screen_surface == NULL) {
			screen_renderer_error_handler(SDL_IMG_OPTI_ERROR);
		}
	}

	if (screen_surface == NULL) {
		return false;
	}
	return true;
}

bool SDL_apply_screen_surface(int x, int y, SDL_Surface* src, SDL_Surface* dest) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	if (SDL_BlitSurface(src, NULL, dest, &offset) < 0) {
		return false;
	}
	return true;
}

int screen_close() {
	int success = 1;

	SDL_FreeSurface(screen_surface);
	screen_surface = NULL;
	if (screen_surface != NULL) {
		success = -1;
		screen_renderer_error_handler(SDL_SCREEN_SURFACE_FREE_ERROR);
	}

	SDL_DestroyWindow(window);
	window = NULL;
	if (window != NULL) {
		success = -1;
		screen_renderer_error_handler(SDL_WINDOW_FREE_ERROR);
	}

	if (success > 0) {
		SDL_Quit();
	}

	return success;
}

void screen_renderer_error_handler(unsigned short error_code) {
	switch (error_code) {
		case 0:
			fputs("Error initializing SDL!\n", stderr);
			break;
		case 1:
			fputs("Error creating SDL window!\n", stderr);
			break;
		case 2:
			fputs("Error initialing SDL window surface!\n", stderr);
			break;
		case 3:
			fputs("Error loading image from path!\n", stderr);
			break;
		case 4:
			fputs("Error optimizing loaded image for screen surface!\n", stderr);
			break;
		case 5:
			fputs("Error loading image for screen surface!\n", stderr);
			break;
		case 6:
			fputs("Error blitting screen surface to window surface!\n", stderr);
			break;
		case 7:
			fputs("Error updating window surface with blitted screen surface!\n", stderr);
			break;
		case 8:
			fputs("Error freeing screen surface!\n", stderr);
			break;
		case 9:
			fputs("Error destroying window!\n", stderr);
			break;
		default:
			fputs("Unknown error code argument in error handler!\n", stderr);
			break;
	}
}
