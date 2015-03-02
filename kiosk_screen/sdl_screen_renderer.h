/*  sdl-screen-1.00.h
 *
 *  Kiosk's screen SDL initialization functions
 *  Functions that are called to initialize the Kiosk's screen window and surface
 */

#ifndef SDL_SCREEN_RENDERER_H_
#define SDL_SCREEN_RENDERER_H_

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern int screen_init(int width, int height, const char* img_path);
/*
 *  Renders Kiosk screen surface in SDL window instance with provided image argument and size
 *  Parameters: int window width, int window height, string literal path to screen image
 *  Return: int
 *          (positive value, successful / negative value, unsuccessful)
 */

extern bool SDL_init();
/*
 *  Initializes SDL library
 *  Parameters: None
 *  Return: bool
 *          (true, successful / false, unsuccessful)
 */

extern bool SDL_window_init(int width, int height);
/*
 *  Initializes SDL window that is centered with provided width and height
 *  Parameters: int window width, int window height
 *  Return: bool
 *          (true, successful / false, unsuccessful)
 */

extern bool SDL_window_surface_init();
/*
 *  Initializes SDL window surface
 *  Parameters: None
 *  Return: bool
 *          (true, successful / false, unsuccessful)
 */

extern bool SDL_load_screen_surface(const char* img_path);
/*
 *  Loads screen surface image and assigns it to SDL surface
 *  Parameters: string literal path to image
 *  Return: bool
 *          (true, successful / false, unsuccessful)
 */

extern bool SDL_apply_screen_surface(int x, int y, SDL_Surface* src, SDL_Surface* dest);
/*
 *  Applies/Blits SDL screen surface to window surface
 *  Parameters: int x_offset, int y_offset, SDL_Surface* screen_surface, SDL_Surface* window_surface
 *  Return: bool
 *          (true, successful / false, unsuccessful)
 */

extern int screen_close();
/*
 *  Deallocates Kiosk screen assets by setting them to NULL and closes SDL subsystems
 *  Parameters: None
 *  Return: int
 *  		(positive, if successful / negative, if unsuccessful)
 */

extern void screen_renderer_error_handler(unsigned short error_code);
/*
 *  Error hander function for debugging
 *  Parameters: unsigned short error code constant
 *  Return: Descriptive error notification string to standard error
 */

#endif /* SDL_SCREEN_RENDERER_H_ */
