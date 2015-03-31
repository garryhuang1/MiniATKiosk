#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "p_kiosk_sdl.h"

struct p_sdl_data {
	SDL_Window *window;
	SDL_Surface *screen_surface;
	SDL_Surface *keypad_surface;
	SDL_Renderer *renderer;
	SDL_Texture *screen_texture;
	SDL_Texture *keypad_texture;
	SDL_Rect text_space;
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

const int S_MIN_X = 324;
const int S_MAX_X = 886;
const int S_MIN_Y = 24;
const int S_MAX_Y = 376;

p_sdl_data * p_sdl_new(void);
int p_sdl_close(p_sdl_data *kiosk);
uint32_t p_sdl_get_mouse_click(p_sdl_data *kiosk, SDL_Event *e);
int p_sdl_clear_screen(p_sdl_data *kiosk);
int p_sdl_render_string(p_sdl_data *kiosk, char string[]);
int p_sdl_render_char(p_sdl_data *kiosk, char c);
int p_sdl_set_text_cursor_x(p_sdl_data *kiosk, int x);
int p_sdl_get_text_cursor_x(p_sdl_data *kiosk);
int p_sdl_set_text_cursor_y(p_sdl_data *kiosk, int y);
int p_sdl_get_text_cursor_x(p_sdl_data *kiosk);
int p_sdl_set_color(p_sdl_data *kiosk, int color);
int p_sdl_get_color(p_sdl_data *kiosk);
int p_sdl_draw_line(p_sdl_data *kiosk, int start_x, int start_y, int end_x, int end_y);
int p_sdl_draw_rectangle(p_sdl_data *kiosk, int x, int y, int height, int width, int dofill);
int p_sdl_draw_pixel(p_sdl_data *kiosk, int x, int y);
int p_sdl_draw_circle(p_sdl_data *kiosk, int x, int y,int radius, int dofill);

/*function p_sdl_new
use to create all the necessary SDL items*/
p_sdl_data * p_sdl_new(void){
	/*create instance of kiosk*/
	p_sdl_data *kiosk;
	kiosk = malloc(sizeof(p_sdl_data));

	/*set default font size*/
	kiosk->font_size = 12;

	bool success =true;

	/*create window*/
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL could not initialized! SDL_Error: %s\n", SDL_GetError());
		success = false;	
	}
	else{
		kiosk->window = SDL_CreateWindow("Kiosk v0.0.2", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
		if(kiosk->window ==NULL){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else{
					/*create renderer*/
			kiosk->renderer = SDL_CreateRenderer(kiosk->window, -1, SDL_RENDERER_ACCELERATED);
			if(kiosk->renderer ==NULL){
				printf("renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else{
				SDL_SetRenderDrawColor(kiosk->renderer, 0x00, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags)& imgFlags)){
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success =false;
				}
			}
		}
	}

	/*render both screen and keypad to the window */
	if(success){
		/*keypad */
		kiosk->keypad_surface = IMG_Load("/home/quw/miniat_t/peripherals/kiosk/src/images/keypad.png");
		if(kiosk->keypad_surface ==NULL){
			printf("Unable to load image %s! SDL_Image Error: %s\n", "src/images/keypad.png", IMG_GetError());
		}
		else{
			kiosk->keypad_texture = SDL_CreateTextureFromSurface(kiosk->renderer, kiosk->keypad_surface);
			if (kiosk->keypad_texture ==NULL){
				printf("Unable to create texture for screen! SDL Error: %s\n", SDL_GetError());
				success = false;
			}		
		}

		/*screen */
		kiosk->screen_surface = IMG_Load("/home/quw/miniat_t/peripherals/kiosk/src/images/screen.png");
		if(kiosk->screen_surface ==NULL){
			printf("Unable to load image %s! SDL_Image Error: %s\n", "src/images/screen.png", IMG_GetError());
		}
		else{
			kiosk->screen_texture = SDL_CreateTextureFromSurface(kiosk->renderer, kiosk->screen_surface);
			if (kiosk->screen_texture ==NULL){
				printf("Unable to create texture for screen! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
		}

		/*display both keypad and screen*/
		SDL_FreeSurface(kiosk->keypad_surface);
		SDL_FreeSurface(kiosk->screen_surface);
		SDL_Rect DestR;
		DestR.x = 0;
		DestR.y = 0;
		DestR.w = 300;
		DestR.h = 400;
		SDL_RenderCopy(kiosk->renderer, kiosk->keypad_texture, NULL, &DestR);
		DestR.x = 300;
		DestR.w = 610;
		SDL_RenderCopy(kiosk->renderer, kiosk->screen_texture, NULL, &DestR);
		SDL_RenderPresent(kiosk->renderer);
	}

	/* initialize SDL_ttf subsystems for kiosk use */
	if (TTF_Init() == -1) {
		printf("Error initializing SDL_ttf subsystem! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		kiosk->text_font = NULL;
		kiosk->text_cursor_x = 325;	// Magic Numbers!
		kiosk->text_cursor_y = 25;	// Magic Numbers!
		kiosk->text_line_size = 0;

		/* Open font ttf file and load into font variable */
		kiosk->text_font = TTF_OpenFont("/home/quw/miniat_t/peripherals/kiosk/src/fonts/pt_sans_regular.ttf", kiosk->font_size);

		if (kiosk->text_font == NULL) {
			printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		}
	}

	/* Default color settings to black*/
	kiosk->color.r = 0;
	kiosk->color.g = 0;
	kiosk->color.b = 0;
	
	/* Initialize text space variable */
	kiosk->text_space.x = 325;
	kiosk->text_space.y = 25;
	kiosk->text_space.w = 0;
	kiosk->text_space.h = kiosk->font_size;

	return kiosk;	
}

/*function p_sdl_close
use to close the sdl library*/
int p_sdl_close(p_sdl_data *kiosk){
	/*destory texutres*/
	SDL_DestroyTexture(kiosk->keypad_texture);
	SDL_DestroyTexture(kiosk->screen_texture);
	kiosk->keypad_texture = NULL;
	kiosk->screen_texture = NULL;

	/*destory window and renderer*/
	SDL_DestroyRenderer(kiosk->renderer);
	SDL_DestroyWindow(kiosk->window);
	kiosk->renderer = NULL;
	kiosk->window = NULL;

	/*quit sdl system*/
	IMG_Quit();
	SDL_Quit();

	if(kiosk->window ==NULL){
		return 1;
	}
	else{
		return 0;
	}
}

/*function p_sdl_get_mouse_click
use to return the last selected value as 32 bits binary, return -1 if nothing is available*/
uint32_t p_sdl_get_mouse_click(p_sdl_data *kiosk, SDL_Event *e){
	uint32_t data = 0x00000000;
	int c, r;

	if(e->type == SDL_MOUSEBUTTONDOWN){
		SDL_GetMouseState(&kiosk->mouse_cursor_x, &kiosk->mouse_cursor_y);

		if(kiosk->mouse_cursor_x <=300 && kiosk->mouse_cursor_y<=400){
		c = (kiosk->mouse_cursor_x/100+1);
		r = (kiosk->mouse_cursor_y/100+4);
		data = ((~((~data)<<c)) ^(~((~data)<<c-1))) | ((~((~data)<<r)) ^(~((~data)<<r-1)));
		return data;
		}
		else{
			return -1;
		}
	}
}

/*  function p_sdl_render_string
 *  Render a string to the screen
 *  Returns 0 if success, 1 if error
 */
int p_sdl_render_string(p_sdl_data *kiosk, char string[]) {
	int success = 0;
	int str_len = 0;
	SDL_Texture *texture = NULL;

	while (string[str_len] != '\0') {
		str_len++;
	}
	str_len--;

	/* Check if string to render will bypass screen boundry */
	/* If so, reset x-axis and increment y-axis by font size */
	if ( (kiosk->text_line_size + str_len * kiosk->font_size) > (610 - 50)) {
		kiosk->text_cursor_x = 325;	// Magic numbers galore!
		kiosk->text_line_size = 0;
		if ( (kiosk->text_cursor_y + kiosk->font_size) > (400 - 25)) {
			success = 1;
			printf("Text cannot render! Screen is full.\n");
		}
		kiosk->text_cursor_y = kiosk->text_cursor_y + kiosk->font_size;
		kiosk->text_line_size = str_len * kiosk->font_size;
	}
	else {
		kiosk->text_line_size += str_len * kiosk->font_size;
	}

	/*Create texture from string*/
	if (success == 0) {
		texture = TTF_RenderText_Solid(kiosk->text_font, (const char *)string, kiosk->color);
		if (texture == NULL) {
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
			success = 1;
		}
		if (success == 0) {	
			texture = SDL_CreateTextureFromSurface(kiosk->renderer, texture);
		}
	}

	/*Render string to screen*/
	if (success == 0) {
		kiosk->text_space.x = kiosk->text_cursor_x;
		kiosk->text_space.y = kiosk->text_cursor_y;
		kiosk->text_space.w = str_len * kiosk->font_size;

		SDL_RenderCopyEx(kiosk->renderer, texture, NULL, &kiosk->text_space, 0.0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(kiosk->renderer);

		/*Update text cursor x positions*/
		kiosk->text_cursor_x = kiosk->text_cursor_x + str_len * kiosk->font_size;
	}

	return success;
}

/*  function p_sdl_render_char
 *  Render a character to the screen
 *  Returns 0 if success, 1 if error
 */
int p_sdl_render_char(p_sdl_data *kiosk, char c) {
	int success = 0;
	const char * character = &c;
	SDL_Texture *texture = NULL;

	/* Check if char to render will intersect boundry */
	/* If so, reset x axis and create newline by incrementing y */
	if ( (kiosk->text_line_size + kiosk->font_size) > (610 - 50) ) {
		kiosk->text_cursor_x = 325;
		kiosk->text_line_size = 0;
		if ( (kiosk->text_cursor_y + kiosk->font_size) > (400 - 25)) {
                        success = 1;
                        printf("Text cannot render! Screen is full.\n");

                }
                kiosk->text_cursor_y = kiosk->text_cursor_y + kiosk->font_size;
		kiosk->text_line_size = kiosk->text_line_size + kiosk->font_size;
	}
	else {
		kiosk->text_line_size += kiosk->font_size;
	}

	/* Create texture of character */
	if (success == 0) {
		texture = TTF_RenderText_Solid(kiosk->text_font, character, kiosk->color);
		if (texture == NULL) {
			 printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
                        success = 1;
		}
		if (success == 0) {
			texture = SDL_CreateTextureFromSurface(kiosk->renderer, texture);
		}
	}
	
	/* Render character to screen */
	if (success == 0) {
		kiosk->text_space.x = kiosk->text_cursor_x;
		kiosk->text_space.y = kiosk->text_cursor_y;
		kiosk->text_space.w = kiosk->font_size;

		SDL_RenderCopyEx(kiosk->renderer, texture, NULL, &kiosk->text_space, 0.0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(kiosk->renderer);

		/*Update text cursor x positions*/
		kiosk->text_cursor_x = kiosk->text_cursor_x + kiosk->font_size;
	}

	return success;
}

/*function p_sdl_set_text_cursor_x
use to set the sdl cursor x value to user define value*/
int p_sdl_set_text_cursor_x(p_sdl_data *kiosk, int x){
	x = x+324;
	kiosk->text_cursor_x = x;
	if((x > S_MAX_X) || (x < S_MIN_X)){
		return 1;
	}
	else if(kiosk->text_cursor_x ==x){
		return 0;
	}
}

/*  function p_sdl_get_text_cursor_x
 *  Text cursor x getter function
 */
int p_sdl_get_text_cursor_x(p_sdl_data *kiosk) {
	return kiosk->text_cursor_x;
}

/*function p_sdl_set_text_cursor_y
use to set the sdl cursor y value to user define value*/
int p_sdl_set_text_cursor_y(p_sdl_data *kiosk, int y){
	y = y+24;
	kiosk->text_cursor_y = y;
	if((y > S_MAX_Y) || (y< S_MIN_Y)){
		return 1;
	}
	else if(kiosk->text_cursor_y ==y){
		return 0;
	}
}

/*  function p_sdl_get_text_cursor_y
 *  Text cursor y getter function
 */
int p_sdl_get_text_cursor_y(p_sdl_data *kiosk) {
	return kiosk->text_cursor_y;
}

/*function p_sdl_set_color
use to set the sdl renderer color, default color is black*/
int p_sdl_set_color(p_sdl_data *kiosk, int color){
	switch(color){
		case 0:
			kiosk->color.r = 0;
			kiosk->color.g = 0;
			kiosk->color.b = 0;
			kiosk->color.a = 255;
			break;
		case 1:
			kiosk->color.r = 0;
			kiosk->color.g = 0;
			kiosk->color.b = 255;
			kiosk->color.a = 255;
			break;
		case 2:
			kiosk->color.r = 0;
			kiosk->color.g = 255;
			kiosk->color.b = 0;
			kiosk->color.a = 255;
			break;
		case 3:
			kiosk->color.r = 255;
			kiosk->color.g = 0;
			kiosk->color.b = 0;
			kiosk->color.a = 255;
			break;
		case 4:
			kiosk->color.r = 0;
			kiosk->color.g = 255;
			kiosk->color.b = 255;
			kiosk->color.a = 255;
			break;
		case 5:
			kiosk->color.r = 255;
			kiosk->color.g = 0;
			kiosk->color.b = 255;
			kiosk->color.a = 255;
			break;
		case 6:
			kiosk->color.r = 255;
			kiosk->color.g = 255;
			kiosk->color.b = 0;
			kiosk->color.a = 255;
			break;
		case 7:
			kiosk->color.r = 0;
			kiosk->color.g = 191;
			kiosk->color.b = 255;
			kiosk->color.a = 255;
		case 8:
			kiosk->color.r = 255;
			kiosk->color.g = 20;
			kiosk->color.b = 147;
			kiosk->color.a = 255;
			break;
		case 9:
			kiosk->color.r = 0;
			kiosk->color.g = 250;
			kiosk->color.b = 154;
			kiosk->color.a = 255;
			break;
		case 10:
			kiosk->color.r = 128;
			kiosk->color.g = 0;
			kiosk->color.b = 128;
			kiosk->color.a = 255;
			break;
		default:
			printf("ERROR INPUT, changing color to black\n");
			kiosk->color.r = 0;
			kiosk->color.g = 0;
			kiosk->color.b = 0;
			kiosk->color.a = 255;
			break;
			return 1;
		}
		SDL_SetRenderDrawColor(kiosk->renderer, kiosk->color.r, kiosk->color.g, kiosk->color.b, kiosk->color.a);
		
		return 0;
}

/*  function p_sdl_get_color
 *  SDL Color getter function
 */
int p_sdl_get_color(p_sdl_data *kiosk) {
	int r = kiosk->color.r;
	int g = kiosk->color.g;
	int b = kiosk->color.b;

	if (r == 0 && g == 0 && b == 0) {
		return 0;
	}
	else if (r == 0 && g == 0 && b == 255) {
		return 1;
	}
	else if (r == 0 && g == 255 && b == 0) {
		return 2;
	}
	else if (r == 255 && g == 0 && b == 0) {
		return 3;
	}
	else if (r == 0 && g == 255 && b == 255) {
		return 4;
	}
	else if (r == 255 && g == 0 && b == 255) {
		return 5;
	}
	else if (r == 255 && g == 255 && b == 0) {
		return 6;
	}
	else if (r == 0 && g == 191 && b == 255) {
		return 7;
	}
	else if (r == 255 && g == 20 && b == 147) {
		return 8;
	}
	else if (r == 0 && g == 250 && b == 154) {
		return 9;
	}
	else if (r == 128 && g == 0 && b == 128) {
		return 10;
	}
	else {
		return -1;
	}
}

/*function p_sdl_clear_screen
use to clear the screen*/
int p_sdl_clear_screen(p_sdl_data *kiosk){
		SDL_Rect DestR;
		DestR.x = 300;
		DestR.y = 0;
		DestR.w = 610;
		DestR.h = 400;
	if(SDL_RenderCopy(kiosk->renderer, kiosk->screen_texture, NULL, &DestR) ==0){
		SDL_RenderPresent(kiosk->renderer);
		return 0;
	}
	else{
		return 1;
	}
}

/* function p_sdl_draw_line
use to draw line on the sdl screen*/
int p_sdl_draw_line(p_sdl_data *kiosk, int start_x, int start_y, int end_x, int end_y){
	if((start_x<S_MIN_X) || (start_x>S_MAX_X) || (start_y <S_MIN_Y) || (start_y > S_MAX_Y)){
		printf("Invalid area to start with !\n");
		return 1;	
	}
	else if ((end_x < S_MIN_X) || (end_x > S_MAX_X) || (end_y < S_MIN_Y) || (end_y> S_MAX_Y)){
		printf("Error, Unable to draw line outside the screen!\n");
		return 1;
	}
	else{
		if(SDL_RenderDrawLine(kiosk->renderer, start_x, start_y, end_x, end_y) !=0){
			printf("fail to draw the line! SDL Error: %s\n", SDL_GetError());
			return 1;
		}
		else{
			SDL_RenderPresent(kiosk->renderer);
			return 0;
		}
	}

}

/* function p_sdl_draw rectangle
use to draw rectangle on the sdl screen*/
int p_sdl_draw_rectangle(p_sdl_data *kiosk, int x, int y, int height, int width, int dofill){
	if((x <S_MIN_X) || (x > S_MAX_X) || (y<S_MIN_Y) ||(y>S_MAX_Y)){
		printf("Invalid area to start with!\n");
		return 1;
	}
	else if ((x+width <S_MIN_X) ||(x+width > S_MAX_X) || (y+height <S_MIN_Y) ||(y+height >S_MAX_Y)){
		printf("Error, Unable to draw rectangle outside the screen!\n");
		return 1;
	}
	else{
		if(dofill ==1){
			SDL_Rect fillRect = {x, y, width, height};
			if(SDL_RenderFillRect(kiosk->renderer, &fillRect) !=0){
				printf("fail to draw a rectangle! SDL Error:%s\n", SDL_GetError());
				return 1;
			}
			else{
				SDL_RenderPresent(kiosk->renderer);
				return 0;
			}
		}
		else if(dofill ==0){
			SDL_Rect outlineRect = {x, y, width, height};
			if(SDL_RenderDrawRect(kiosk->renderer, &outlineRect) !=0){
				printf("fail to draw a rectangle! SDL Error: %s\n", SDL_GetError());
				return 1;
			}
			else{
				SDL_RenderPresent(kiosk->renderer);
				return 0;
			}
		}
		else{
			printf("Error input!\n");
			return 1;
		}
	}
}

/*function p_sdl_draw_pixel
use to plot a pixel at user defined position*/
int p_sdl_draw_pixel(p_sdl_data *kiosk, int x, int y){
	if((x<S_MIN_X) || (x>S_MAX_X) || (y<S_MIN_Y) || (y>S_MAX_Y)){
		printf("Invalid area to start with! x is: %d and y is: %d\n", x, y);
		return 1;
	}
	else{
		if(SDL_RenderDrawPoint(kiosk->renderer, x, y) !=0){
			printf("fail to draw the line! SDL Error: %s\n", SDL_GetError());
			return 1;
		}
		else{
			SDL_RenderPresent(kiosk->renderer);
			return 0;
		}
	}
}

/*function p_sdl_draw_circle
use to draw a circle on the screen*/
int p_sdl_draw_circle(p_sdl_data *kiosk, int x, int y,int radius, int dofill){
	if((x<S_MIN_X) || (x>S_MAX_X) || (y<S_MIN_Y) || (y>S_MAX_Y)){
		printf("Invalid area to start with! x is: %d and y is: %d\n", x, y);
		return 1;
	}
	else if((x+radius > S_MAX_X) || (x-radius < S_MIN_X) || (y+radius > S_MAX_Y) || (y-radius < S_MIN_Y)){
		printf("Error, Unable to draw rectangle outside the screen!\n");
		return 1;
	}
	else{
		if(dofill == 1){
			if(filledCircleColor(kiosk->renderer, x, y, radius, ((kiosk->color.a<<24) | (kiosk->color.b<<16) | (kiosk->color.g <<8) | (kiosk->color.r))) !=0){
				printf("fail to draw the circle!\n");
				return 1;
			}
			else{
				SDL_RenderPresent(kiosk->renderer);
				return 0;
			}
		}
		else if (dofill == 0){
			if(circleRGBA(kiosk->renderer, x, y, radius, kiosk->color.r, kiosk->color.g, kiosk->color.b, kiosk->color.a) != 0){
				printf("fail to draw the circle!\n");
				return 1;
			}
			else{
				SDL_RenderPresent(kiosk->renderer);
				return 0;
			}
		}
		else{
			printf("Error input!\n");
			return 1;
		}
	}
}

int main (void) {
	return 0;
}
