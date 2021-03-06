#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "p_kiosk_sdl.h"

#define S_MIN_X 329
#define S_MAX_X 881
#define S_MIN_Y 29
#define S_MAX_Y 371

#define PS_MIN_X 910
#define PS_MAX_X 1100
#define PS_MIN_Y 14
#define PS_MAX_Y 189

#define PRINTER_FILENAME "receipt-current.txt"

#define SCREEN_LINE_HEIGHT 20
#define SCREEN_FONT_WIDTH 14

#define PRINTER_LINE_HEIGHT 20
#define PRINTER_FONT_WIDTH 18

p_sdl_data * p_sdl_new(void);
int p_sdl_close(p_sdl_data *kiosk);
uint32_t p_sdl_get_mouse_click(p_sdl_data *kiosk);
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
int p_sdl_reset(p_sdl_data *kiosk);
int p_sdl_get_event(p_sdl_data *kiosk);
int p_sdl_draw_screen(p_sdl_data *kiosk);
int p_sdl_receipt_cut(p_sdl_data *kiosk);

int p_sdl_set_receipt_cursor_x(p_sdl_data *kiosk, int x);
int p_sdl_set_receipt_cursor_y(p_sdl_data * kiosk, int y);
int p_sdl_get_receipt_cursor_x(p_sdl_data *kiosk);
int p_sdl_get_receipt_cursor_y(p_sdl_data *kiosk);
int p_sdl_receipt_printer_new_line(p_sdl_data *kiosk);
int p_sdl_receipt_render_char(p_sdl_data *kiosk, char character);

int priv_sdl_render(p_sdl_data *kiosk);
int priv_sdl_font_init(p_sdl_data *kiosk);

/*function p_sdl_new
use to create all the necessary SDL items*/
p_sdl_data * p_sdl_new(void){
	/*create instance of kiosk*/
	p_sdl_data *kiosk;
	kiosk = malloc(sizeof(p_sdl_data));
	
	/*create window*/
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL could not initialized! SDL_Error: %s\n", SDL_GetError());
		
		return NULL;
		
	} else {
		kiosk->window = SDL_CreateWindow("Kiosk v2.9.9", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WINDOW_WIDTH, WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
		if(kiosk->window == NULL){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError() );
			
			return NULL;
			
		} else {
			if (priv_sdl_render(kiosk) == 0) {
				
				if (priv_sdl_font_init(kiosk) == 0)
					{
						kiosk->receipt_print = fopen(PRINTER_FILENAME, "w");
						if(!kiosk->receipt_print){
							printf("fail to create file\n");
						}
						return kiosk;	
					} else {
						return NULL;
					}
			} else {
				return NULL;
			}
		}
	}

	return NULL;

	
}

/*function p_sdl_close
use to close the sdl library*/
int p_sdl_close(p_sdl_data *kiosk){
	/*destory texutres*/
	SDL_DestroyTexture(kiosk->keypad_texture);
	SDL_DestroyTexture(kiosk->screen_texture);
	SDL_DestroyTexture(kiosk->print_screen_texture);
	kiosk->keypad_texture = NULL;
	kiosk->screen_texture = NULL;
	kiosk->print_screen_texture = NULL;

	/*destory window and renderer*/
	SDL_DestroyRenderer(kiosk->renderer);
	SDL_DestroyWindow(kiosk->window);
	kiosk->renderer = NULL;
	kiosk->window = NULL;

	/*quit sdl system*/
	IMG_Quit();
	SDL_Quit();

	fclose(kiosk->receipt_print);
	return 0;

}


/* Private function: renders the kiosk resources */
int priv_sdl_render(p_sdl_data *kiosk)
{
	
	kiosk->renderer = SDL_CreateRenderer(kiosk->window, -1, SDL_RENDERER_ACCELERATED);
	
	if(kiosk->renderer == NULL){
		printf("renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return 1;
	} else {

		int color_set = p_sdl_set_color(kiosk, 0);
		
		if (color_set != 0)
			{
				return color_set;
			}
		
		int imgFlags = IMG_INIT_PNG;
		if(!(IMG_Init(imgFlags)& imgFlags)){
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			return 1;
		}
		
		kiosk->keypad_surface = NULL;
		kiosk->screen_surface = NULL;
		kiosk->print_screen_surface = NULL;
		
		/* Display keypad */
		kiosk->keypad_surface = IMG_Load("system/kiosk/resources/images/keypad.png");
		if(kiosk->keypad_surface == NULL){
			printf("Unable to load image %s! SDL_Image Error: %s\n", "resources/images/keypad.png", IMG_GetError());
		} else {
			kiosk->keypad_texture = SDL_CreateTextureFromSurface(kiosk->renderer, kiosk->keypad_surface);
			if (kiosk->keypad_texture == NULL){
				printf("Unable to create texture for screen! SDL Error: %s\n", SDL_GetError());
				return 1;
			}		
		}

		/* Display screen */
		kiosk->screen_surface = IMG_Load("system/kiosk/resources/images/screen.png");
		if(kiosk->screen_surface ==NULL){
			printf("Unable to load image %s! SDL_Image Error: %s\n", "resources/images/screen.png", IMG_GetError());
		}
		else{
			kiosk->screen_texture = SDL_CreateTextureFromSurface(kiosk->renderer, kiosk->screen_surface);
			if (kiosk->screen_texture ==NULL){
				printf("Unable to create texture for screen! SDL Error: %s\n", SDL_GetError());
				return 1;
			}
		}
		
		/* Display printer */
		kiosk->print_screen_surface = IMG_Load("system/kiosk/resources/images/print_screen.png");
		if(kiosk->print_screen_surface ==NULL){
			printf("Unable to load image %s! SDL_Image Error: %s\n", "resources/images/screen.png", IMG_GetError());
		}
		else{
			kiosk->print_screen_texture = SDL_CreateTextureFromSurface(kiosk->renderer, kiosk->print_screen_surface);
			if (kiosk->print_screen_texture ==NULL){
				printf("Unable to create texture for screen! SDL Error: %s\n", SDL_GetError());
				return 1;
			}
		}
		
		SDL_FreeSurface(kiosk->keypad_surface);
		SDL_FreeSurface(kiosk->screen_surface);
		SDL_FreeSurface(kiosk->print_screen_surface);
		
		kiosk->keypad_dest.x = 0;
		kiosk->keypad_dest.y = 0;
		kiosk->keypad_dest.w = 300;
		kiosk->keypad_dest.h = 400;
		SDL_RenderCopy(kiosk->renderer, kiosk->keypad_texture, NULL, &kiosk->keypad_dest);
		
		kiosk->screen_dest.x = 300;
		kiosk->screen_dest.y = 0;
		kiosk->screen_dest.w = 610;
		kiosk->screen_dest.h = 400;
		SDL_RenderCopy(kiosk->renderer, kiosk->screen_texture, NULL, &kiosk->screen_dest);
		
		kiosk->print_screen_dest.x = 900;
		kiosk->print_screen_dest.y = 0;
		kiosk->print_screen_dest.w = 200;
		kiosk->print_screen_dest.h = 400;
		SDL_RenderCopy(kiosk->renderer, kiosk->print_screen_texture, NULL, &kiosk->print_screen_dest);
		
		// Render
		SDL_RenderPresent(kiosk->renderer);
		
		return 0;
	}
	
	
}

int priv_sdl_font_init(p_sdl_data *kiosk) 
{
	/* initialize SDL_ttf subsystems for kiosk use */
	if (TTF_Init() == -1) {
		printf("Error initializing SDL_ttf subsystem! SDL_ttf Error: %s\n", TTF_GetError());
		return 1;
	}
	else {
		kiosk->text_font = NULL;
		kiosk->text_cursor_x = S_MIN_X;	
		kiosk->text_cursor_y = S_MIN_Y;	

		kiosk->receipt_text_font = NULL;
		kiosk->print_screen_cursor_x = PS_MIN_X;	
		kiosk->print_screen_cursor_y = PS_MIN_Y;
		kiosk->print_text_line_size = 0;
		
		/* Open font ttf file and load into font variable */
		kiosk->text_font = TTF_OpenFont("system/kiosk/resources/fonts/pt_sans_regular.ttf", SCREEN_FONT_WIDTH);

		kiosk->receipt_text_font = TTF_OpenFont("system/kiosk/resources/fonts/pt_sans_regular.ttf", PRINTER_FONT_WIDTH);

		if (kiosk->text_font == NULL || kiosk->receipt_text_font == NULL) {
			printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
			return 1;
		}
	}

	/* Default color settings to black*/
	kiosk->color.r = 0;
	kiosk->color.g = 0;
	kiosk->color.b = 0;
	
	/* Initialize text space variable */
	kiosk->text_space.x = S_MIN_X;
	kiosk->text_space.y = S_MIN_Y;
	kiosk->text_space.w = 0;
	kiosk->text_space.h = SCREEN_LINE_HEIGHT;

	/* Initialize print screen variable*/
	kiosk->print_text_space.x = S_MIN_X;
	kiosk->print_text_space.y = S_MIN_Y;
	kiosk->print_text_space.w = 0;
	kiosk->print_text_space.h = PRINTER_FONT_WIDTH;
	return 0;
}


/*function p_sdl_get_event
use to stroe the latest event into the sdl struct*/
int p_sdl_get_event(p_sdl_data *kiosk){
	//printf("in get event");
	if(SDL_PollEvent(&kiosk->mouse_event) != 0){
		if(kiosk->mouse_event.type == SDL_QUIT){
			return 0;
		}
		else{
			return 1;
		}
	}

}

/*function p_sdl_get_mouse_click
use to return the last selected value as 32 bits binary, return -1 if nothing is available*/
uint32_t p_sdl_get_mouse_click(p_sdl_data *kiosk){
	
	if (SDL_WaitEvent(&kiosk->mouse_event))
		{
			uint32_t data = 0x00000000;
			int c, r;

			if(kiosk->mouse_event.type == SDL_MOUSEBUTTONDOWN){
				SDL_GetMouseState(&kiosk->mouse_cursor_x, &kiosk->mouse_cursor_y);

				if(kiosk->mouse_cursor_x <=300 && kiosk->mouse_cursor_y<=400) {
					c = (kiosk->mouse_cursor_x/100+1);
					r = (kiosk->mouse_cursor_y/100+4);
					data = ((~((~data)<<c)) ^(~((~data)<<c-1))) | ((~((~data)<<r)) ^(~((~data)<<r-1)));
					return data;
				}

			}
			else if (kiosk->mouse_event.type == SDL_QUIT){
				return 0;
			}
			
		} 
	return 0;
}

/*function p_sdl_draw_screen
use to draw pixels on the kiosk screen*/
int p_sdl_draw_screen(p_sdl_data *kiosk){
	if(SDL_WaitEvent(&kiosk->mouse_event)){
		bool mouse_down = false;
		SDL_GetMouseState(&kiosk->mouse_cursor_x, &kiosk->mouse_cursor_y);
		if(kiosk->mouse_event.type == SDL_QUIT){
			return 0;
		}
		else if((kiosk->mouse_cursor_x >S_MIN_X) && (kiosk->mouse_cursor_x < S_MAX_X) && (kiosk->mouse_cursor_y > S_MIN_Y) && (kiosk->mouse_cursor_y < S_MAX_Y)){
			if(kiosk->mouse_event.type == SDL_MOUSEBUTTONDOWN){
				mouse_down = true;
				while(mouse_down){
					if(SDL_WaitEvent(&kiosk->mouse_event) != 0){
						if(kiosk->mouse_event.type == SDL_MOUSEBUTTONUP){
							if(kiosk->mouse_event.button.button == SDL_BUTTON_LEFT){
								mouse_down = false;
								return 1;
							}
						}
						else if (kiosk->mouse_event.type == SDL_MOUSEMOTION){
							SDL_GetMouseState(&kiosk->mouse_cursor_x, &kiosk->mouse_cursor_y);
							if((p_sdl_draw_pixel(kiosk, (kiosk->mouse_cursor_x - S_MIN_X), (kiosk->mouse_cursor_y - S_MIN_Y))) == 1){
								mouse_down = false;
							}
						}
					}
				}
			}
		}
	}
}

/*  function p_sdl_render_string
 *  Render a string to the screen
 *  Returns 0 if success, 1 if error
 */
int p_sdl_render_string(p_sdl_data *kiosk, char string[]) {
	int success = 0;
	size_t str_len;
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = NULL;

	/* Get string length and add NULL terminator if ending in newline*/
	str_len = strlen(string)-1;
	if(string[str_len] == '\n'){
		string[str_len] = '\0';
	}

	/* Check if text cursor out of bounds */
	if (kiosk->text_cursor_x < S_MIN_X || kiosk->text_cursor_x > S_MAX_X) {
		printf("\nText cursor x value out of bounds, %d", kiosk->text_cursor_x);
		success = 1;
	}
	
	if (kiosk->text_cursor_y < S_MIN_Y || kiosk->text_cursor_y > S_MAX_Y ) {
		printf("\nText cursor y value out of bounds, %d", kiosk->text_cursor_y);
		success = 1;
	}

	int line_remaining = S_MAX_X - kiosk->text_cursor_x;
	int string_display_length = str_len * SCREEN_FONT_WIDTH;
	
	if (line_remaining < string_display_length) {
		
		printf("\nString is too long\n");
		success = 1;
		
	} else {
		surface = TTF_RenderText_Solid(kiosk->text_font, (const char *)string, kiosk->color);
		
		if (surface == NULL) {
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
			success = 1;
		} else if (success == 0){
			texture = SDL_CreateTextureFromSurface(kiosk->renderer, surface);

			/* Set x,y coordinates and width of text space where string will render */
			kiosk->text_space.x = kiosk->text_cursor_x;
			kiosk->text_space.y = kiosk->text_cursor_y;

			kiosk->text_space.w = str_len * SCREEN_FONT_WIDTH;

			SDL_RenderCopyEx(kiosk->renderer, texture, NULL, &kiosk->text_space, 0.0, NULL, SDL_FLIP_NONE);
			SDL_RenderPresent(kiosk->renderer);

			/* Update text cursor x positions */
			kiosk->text_cursor_x = kiosk->text_cursor_x + str_len * SCREEN_FONT_WIDTH;
		}
		
		
	}
		return success;
	
}

/*  function p_sdl_render_char
 *  Render a character to the screen
 *  Returns 0 if success, 1 if error
 */
int p_sdl_render_char(p_sdl_data *kiosk, char c) {
	int success = 0;
	
	char character[2] = {c, '\0'};
	
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = NULL;
	
	/* Check if text cursor out of bounds */
	if (kiosk->text_cursor_x < S_MIN_X || kiosk->text_cursor_x > S_MAX_X) {
		printf("\nText cursor x value out of bounds, %d", kiosk->text_cursor_x);
		success = 1;
	}
	if (kiosk->text_cursor_y < S_MIN_Y || kiosk->text_cursor_y > S_MAX_Y) {
		printf("\nText cursor y value out of bounds, %d", kiosk->text_cursor_y);
		success = 1;
	}

	/* Check if char to render will intersect boundary */
	/* If so, reset x axis and create newline by incrementing y */
	
	int line_remaining = S_MAX_X - kiosk->text_cursor_x;
		
	if (line_remaining < SCREEN_FONT_WIDTH) {
		kiosk->text_cursor_x = S_MIN_X;
		
		if ( (kiosk->text_cursor_y + SCREEN_LINE_HEIGHT) > S_MAX_Y ) {
				success = 1;
				printf("Text cannot render! Screen is full.\n");
		} else {
			kiosk->text_cursor_y += SCREEN_LINE_HEIGHT;
		}

	}
	
	if (success == 0) {
		surface = TTF_RenderText_Solid(kiosk->text_font, character, kiosk->color);
		
		if (surface == NULL) {
			 printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
             success = 1;
		} else {
			texture = SDL_CreateTextureFromSurface(kiosk->renderer, surface);
			
			kiosk->text_space.x = kiosk->text_cursor_x;
			kiosk->text_space.y = kiosk->text_cursor_y;
			kiosk->text_space.w = SCREEN_FONT_WIDTH;

			SDL_RenderCopyEx(kiosk->renderer, texture, NULL, &kiosk->text_space, 0.0, NULL, SDL_FLIP_NONE);
			SDL_RenderPresent(kiosk->renderer);

			/*Update text cursor x positions*/
			kiosk->text_cursor_x = kiosk->text_cursor_x + SCREEN_FONT_WIDTH;
		}

	}
	
	return success;

	
}

/*function p_sdl_set_text_cursor_x
use to set the sdl cursor x value to user define value*/
int p_sdl_set_text_cursor_x(p_sdl_data *kiosk, int x){
	x = x + S_MIN_X;
	if((x > S_MAX_X) || (x < S_MIN_X)){
		return 1;
	}
	else {
		kiosk->text_cursor_x = x;
		return 0;
	}
}

/*  function p_sdl_get_text_cursor_x
 *  Text cursor x getter function
 */
int p_sdl_get_text_cursor_x(p_sdl_data *kiosk) {
	return kiosk->text_cursor_x - S_MIN_X;
}

/*function p_sdl_set_text_cursor_y
use to set the sdl cursor y value to user define value*/
int p_sdl_set_text_cursor_y(p_sdl_data *kiosk, int y){
	y = y + S_MIN_Y;
	if((y >= S_MAX_Y) || (y <= S_MIN_Y || y + SCREEN_LINE_HEIGHT > S_MAX_Y)) {
		return 1;
	}
	else {
		kiosk->text_cursor_y = y;
		return 0;
	}
}

/*  function p_sdl_get_text_cursor_y
 *  Text cursor y getter function
 */
int p_sdl_get_text_cursor_y(p_sdl_data *kiosk) {
	return kiosk->text_cursor_y - S_MIN_Y;
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
			return 1;
			break;
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
	if(SDL_RenderCopy(kiosk->renderer, kiosk->screen_texture, NULL, &kiosk->screen_dest) == 0){
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
	start_x = start_x + S_MIN_X;
	start_y = start_y + S_MIN_Y;
	
	end_x = end_x + S_MIN_X;
	end_y = end_y + S_MIN_Y;
	
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
	x = x + S_MIN_X;
	y = y + S_MIN_Y;
	if((x <S_MIN_X) || (x > S_MAX_X) || (y<S_MIN_Y) ||(y>S_MAX_Y)){
		printf("Invalid area to start with!\n");
		return 1;
	}
	else if ((x+width <S_MIN_X) ||(x+width > S_MAX_X) || (y+height <S_MIN_Y) ||(y+height >S_MAX_Y)){
		printf("Error, Unable to draw rectangle outside the screen!\n");
		return 1;
	}
	else{
		if(dofill == 1){
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
		else if(dofill == 0){
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
			printf("Error! Invalid dofill argument value!");
			return 1;
		}
	}
}

/*function p_sdl_draw_pixel
use to plot a pixel at user defined position*/
int p_sdl_draw_pixel(p_sdl_data *kiosk, int x, int y){
	x = x + S_MIN_X;
	y = y + S_MIN_Y;
	if((x<S_MIN_X) || (x>S_MAX_X) || (y<S_MIN_Y) || (y>S_MAX_Y)){
		printf("Invalid area to start with! x is: %d and y is: %d\n", x, y);
		return 1;
	}
	else{
		if(SDL_RenderDrawPoint(kiosk->renderer, x, y) !=0){
			printf("fail to draw the pixel! SDL Error: %s\n", SDL_GetError());
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
int p_sdl_draw_circle(p_sdl_data *kiosk, int x, int y, int radius, int dofill){

	x = x + S_MIN_X;
	y = y + S_MIN_Y;
	if((x<S_MIN_X) || (x>S_MAX_X) || (y<S_MIN_Y) || (y>S_MAX_Y)){
		printf("Invalid area to start with! x is: %d and y is: %d\n", x, y);
		return 1;
	}
	else if((x+radius > S_MAX_X) || (x-radius < S_MIN_X) || (y+radius > S_MAX_Y) || (y-radius < S_MIN_Y)){
		printf("Error, Unable to draw circle outside the screen!\n");
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
			printf("Error! Invalid dofill argument value!");
			return 1;
		}
	}
}

/*function p_sdl_reset_values
Use to reset the values of p_sdl_data to default values set in init*/
int p_sdl_reset(p_sdl_data *kiosk) {
	int success = 0;
	int imgFlags = IMG_INIT_PNG;
	
	/* Reset renderer */
	SDL_DestroyRenderer(kiosk->renderer);
	
	if (priv_sdl_render(kiosk) == 0) {
		if ( priv_sdl_font_init(kiosk) == 0 ) {
			return 0;
		}else {
			return 1;
		}
	} else {
		return 1;
	}
	
	
	return 1;
}




int p_sdl_set_receipt_cursor_x(p_sdl_data *kiosk, int x){
	x = x + PS_MIN_X;
	if((x > PS_MAX_X) || (x < PS_MIN_X)){
		return 1;
	}
	else {
		kiosk->print_screen_cursor_x = x;
		return 0;
	}
}
int p_sdl_set_receipt_cursor_y(p_sdl_data *kiosk, int y){
	y = y + PS_MIN_Y;
	if((y > PS_MAX_Y) || (y < PS_MIN_Y)){
		return 1;
	}
	else {
		kiosk->print_screen_cursor_y = y;
		return 0;
	}
}
int p_sdl_get_receipt_cursor_x(p_sdl_data *kiosk) {
	return kiosk->print_screen_cursor_y - PS_MIN_X;
}
int p_sdl_get_receipt_cursor_y(p_sdl_data *kiosk) {
	return kiosk->print_screen_cursor_y - PS_MIN_Y;
}
int p_sdl_receipt_printer_new_line(p_sdl_data *kiosk){
	if(SDL_RenderCopy(kiosk->renderer, kiosk->print_screen_texture, NULL, &kiosk->print_screen_dest) == 0){
		SDL_RenderPresent(kiosk->renderer);
		kiosk->print_screen_cursor_x = PS_MIN_X;
		kiosk->print_screen_cursor_y = PS_MIN_Y;
		kiosk->print_text_line_size = 0;
		fputc('\n', kiosk->receipt_print);
		return 0;
	}
	else{
		return 1;
	}
}
int p_sdl_receipt_render_char(p_sdl_data *kiosk, char c){
	//printf("in render char\n");
	int success = 0;
	const char * character = &c;
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = NULL;

	/* Check if text cursor out of bounds */
	if (kiosk->print_screen_cursor_x < PS_MIN_X || kiosk->print_screen_cursor_x > PS_MAX_X) {
		printf("\nText cursor x value out of bounds, %d\n", kiosk->print_screen_cursor_x);
		success = 1;
	}
	if (kiosk->print_screen_cursor_y < PS_MIN_Y || kiosk->print_screen_cursor_y > PS_MAX_Y) {
		printf("\nText cursor y value out of bounds, %d\n", kiosk->print_screen_cursor_y);
		success = 1;
	}

	/* Check if char to render will intersect boundry */
	/* If so, reset x axis and create newline by incrementing y */
	if ( (kiosk->print_text_line_size + PRINTER_FONT_WIDTH) > (PS_MAX_X - PS_MIN_X) && success == 0) {
		kiosk->print_screen_cursor_x = PS_MIN_X;
		kiosk->print_text_line_size = 0;
		if ( (kiosk->print_screen_cursor_y + PRINTER_LINE_HEIGHT) > PS_MAX_Y) {
                        success = 1;
                        printf("Text cannot render! Printer Screen is full.\n");

                }
                kiosk->print_screen_cursor_y = kiosk->print_screen_cursor_y + PRINTER_LINE_HEIGHT;
		kiosk->print_text_line_size = kiosk->print_text_line_size + PRINTER_FONT_WIDTH;
	}
	else {
		kiosk->print_text_line_size += PRINTER_FONT_WIDTH;
	}

	/* Create texture of character */
	if (success == 0) {
		surface = TTF_RenderText_Solid(kiosk->text_font, character, kiosk->color);
		if (surface == NULL) {
			 printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
                        success = 1;
		}
		if (success == 0) {
			texture = SDL_CreateTextureFromSurface(kiosk->renderer, surface);
		}
	}
	
	/* Render character to screen */
	if (success == 0) {
		kiosk->print_text_space.x = kiosk->print_screen_cursor_x;
		kiosk->print_text_space.y = kiosk->print_screen_cursor_y;
		kiosk->print_text_space.w = PRINTER_FONT_WIDTH;

		SDL_RenderCopyEx(kiosk->renderer, texture, NULL, &kiosk->print_text_space, 0.0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(kiosk->renderer);

		/*Update text cursor x positions*/
		kiosk->print_screen_cursor_x = kiosk->print_screen_cursor_x + PRINTER_FONT_WIDTH;

		fputc(c, kiosk->receipt_print);
	}

	return success;	
}

int p_sdl_receipt_cut(p_sdl_data *kiosk) {
	char new_name[] = "receipt-";
	char current_name[] = PRINTER_FILENAME;
	char ext[] = ".txt";
	char time_string[18];
	char final[sizeof(new_name) + sizeof(time_string) + sizeof(ext)];
	
	
	
	
	
	time_t time_item;
	struct tm *time_struct;

	time_item = time(NULL);
	time_struct = localtime(&time_item);
	
	if (time_struct == NULL) {
	   printf("Error occured while getting time");
	   return 1;
	}

	if (strftime(time_string, sizeof(time_string), "%F-%H%M%S", time_struct) == 0) {
		printf("Error occured while getting time string");
		return 1;
	}else{
		strcpy(final, new_name);
		strcat(final, time_string);
		strcat(final, ext);
		
		printf("Moving file to %s", final);
		
		fclose(kiosk->receipt_print);
		
		if (rename(current_name, final) == 0) {
			kiosk->receipt_print = fopen(PRINTER_FILENAME, "w");
			return 0;
		} else {
			printf("Error occured while renaming file");
			return 1;
		}
		
		
		
		
	}

	
}
