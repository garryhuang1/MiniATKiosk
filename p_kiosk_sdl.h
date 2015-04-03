#ifndef _P_KIOSK_SDL_H_
#define _P_KIOSK_SDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int WINDOW_WIDTH = 910;
/**
 * Global constant variable for window width.
 */

const int WINDOW_HEIGHT = 400;
/**
 * Global constant variable for window height.
 */

const int SCREEN_WIDTH = 610;
/**
 * Global constant variable for screen width.
 */

const int SCREEN_HEIGHT = 400;
/**
 * Global constant variable for screen width.
 */

struct p_sdl_data {
	SDL_Window *window;
	SDL_Surface *screen_surface;
	SDL_Surface *keypad_surface;
	SDL_Renderer *renderer;
	SDL_Texture *screen_texture;
	SDL_Texture *keypad_texture;
	SDL_Rect text_space;
	SDL_Rect keypad_dest;
	SDL_Rect screen_dest;
	TTF_Font *text_font;
	SDL_Texture *pixel_texture;
	int mouse_cursor_x;
	int mouse_cursor_y;
	int font_size;
	int text_cursor_x;
	int text_cursor_y;
	int text_line_size;
	SDL_Color color;
};

typedef struct p_sdl_data p_sdl_data;
/**
 * Creates an instance of a Kiosk SDL data structure 
 * defined in the implementation file called "p_sdl_data".
 * The Kiosk SDL data struct will contain pointers to 
 * neccessary SDL structs that contain data to render
 * the window, screen surfaces for the keypad and 
 * screen, the renderer, cursor x and y positions, and
 * the window width and height.
 * 
 * @param none
 * 
 * @return none
 */

extern p_sdl_data * p_sdl_new(void);
/**
 * Creates all necessary SDL items, renders the items, 
 * and returns the p_sdl_data struct.
 * 
 * @param none
 *
 * @return p_sdl_data pointer
 *	The status of the function executed	
 */

extern int p_sdl_close(p_sdl_data * kiosk);
/**
 * Closes all opened SDL items.
 * 
 * @param p_sdl_data * kiosk
 * 	The SDL data struct
 * @return int
 * 	The status of the function executed	
 */

extern uint32_t p_sdl_get_mouse_click(p_sdl_data * kiosk, SDL_Event *e);
/**
 * Gets last selected value where the mouse was
 * clicked.
 * 
 * @param p_sdl_data * kiosk
 * 	The SDL data struct
 * @return int 
 * 	The status of the function executed
 */

extern int p_sdl_clear_screen(p_sdl_data * kiosk);
/**
 * Clears the Kiosks screen. 
 * 
 * @param p_sdl_data * kiosk
 *      The SDL data struct
 * @return int
 * 	The status of the function executed.
 * 	0 if no error
 */

extern int p_sdl_render_string(p_sdl_data * kiosk, char string[]);
/**
 * Renders the entire string beginning at the 
 * current cursor x and y locations. If the 
 * string is calculated to go off of the screen, 
 * the string is not rendered and an error status 
 * is returned.
 * 
 * @param p_sdl_data * kiosk, char[] string
 * 	The SDL data struct and character string buffer
 * @return int
 * 	The status of the function executed.
 *      0 if no error
 */ 

extern int p_sdl_render_char(p_sdl_data * kiosk, char c);
/**
 * Renders a single character at the current cursor 
 * position. If the cursor is off of the screen, the 
 * character will no be rendered and an error status 
 * is returned
 * 
 * @param p_sdl_data * kiosk, char character
 * 	The SDL data struct and character to render
 * @return int
 * 	The status of the function executed.
 *      0 if no error
 */

extern int p_sdl_set_text_cursor_x(p_sdl_data * kiosk, int x);
/**
 * Sets the text cursor's x location
 * 
 * @param p_sdl_data * kiosk, int x
 * 	The SDL data struct and x value to set 
 * 	cursor.
 * @return int
 * 	0 if no error occurred, 1 if error
 */

extern int p_sdl_get_text_cursor_x(p_sdl_data * kiosk);
/**
 * Gets the text cursor's x location
 * 
 * @param p_sdl_data * kiosk
 * 	The SDL data struct
 * @return int
 * 	x value of text cursor
 */

extern int p_sdl_set_text_cursor_y(p_sdl_data * kiosk, int y);
/**
 * Sets the text cursor's y location
 * 
 * @param p_sdl_data * kiosk, int y
 * 	The SDL data struct and y value to set 
 *      cursor.
 * @return int
 * 	0 if no error occurred, 1 if error
 */

extern int p_sdl_get_text_cursor_y(p_sdl_data * kiosk);
/**
 * Gets the text cursor's y location
 * 
 * @param p_sdl_data * kiosk
 * 	The SDL data struct
 * @return int
 * 	y value of text cursor
 */

extern int p_sdl_set_color(p_sdl_data * kiosk, int color);
/**
 * Sets the current color for text rendering and 
 * drawing corresponding with color code argument.
 *
 * @param p_sdl_data * kiosk, int color
 *	The SDL data struct and color code
 * @return int
 * 	0 if no error occurred, 1 if error
 */

extern int p_sdl_get_color(p_sdl_data * kiosk);
/**
 * Gets the current color for text rendering and 
 * drawing corresponding with color code argument.
 *
 * @param p_sdl_data * kiosk
 * @return int
 * 	int color code, error if -1 returned
 */

extern int p_sdl_draw_line(p_sdl_data * kiosk, int start_x, int start_y, int end_x, int end_y);
/**
 * Draws a line from the start x and y positions 
 * to the end x and y positions with a line 
 * stroke width.
 * 
 * @param p_sdl_data * kiosk, int start_x, int start_y, int end_x, int end_y, int stroke_width
 * 	The SDL data struct, x and y start points, 
 * 	x and y end points, and a line width
 * @return int
 * 	0 if no error, 1 if error
 */ 

extern int p_sdl_draw_rectangle(p_sdl_data * kiosk, int x, int y, int height, int width, int dofill);
/**
 * Sets the current color for text rendering and  
 * drawing. Draws a rectangle.
 * 
 * @param p_sdl_data * kiosk, int x, int y, int height, int width, int dofill
 * 	The SDL data struct, x and y start points, 
 * 	height and width of rectangle, and if 
 * 	rectangle is filled in.
 * @return int
 * 	0 if no error, 1 if error
 */

extern int p_sdl_draw_pixel(p_sdl_data * kiosk, int x, int y);
/**
 * Draws a pixel in the defined x and y 
 * location.
 * 
 * @param p_sdl_data * kiosk, int x, int y
 * 	The SDL data struct, and x and y 
 * 	position of the drawn pixel
 * @return int
 * 	0 if no error, 1 if error
 */

extern int p_sdl_draw_circle(p_sdl_data * kiosk, int x, int y, int radius, int dofill);
/**
 * Draws a circle with the defined x and y 
 * location at its center with a defined 
 * radius and on/off fill
 * 
 * @param p_sdl_data * kiosk, int x, int y, int radius, int dofill
 * 	The SDL data struct, x and y 
 * 	center location, radius, and 
 * 	on, or off, fill.
 * @return int
 * 	0 if no error, 1 if error
 */

extern int p_sdl_reset(p_sdl_data * kiosk);
/**
 *  Resets the p_sdl_data values to default values set in init function
 *  
 * @param p_sdl_data * kiosk
 * 	The SDL data struct
 * 	@return int
 * 	0 if no error, 1 if error
 */

#endif
