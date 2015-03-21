#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
	int window_width;
	int window_height;
	SDL_Window *window;
	SDL_Surface *window_surface;
	SDL_Surface *screen_surface;
	SDL_Surface *keypad_surface;
	SDL_Rect upper_right; //new added variable 
	SDL_Renderer *renderer;
	int cursor_x;
	int cursor_y;
	int color;
}p_sdl_data;

p_sdl_data * p_sdl_new(void);
int p_sdl_close(p_sdl_data *kiosk);
uint32_t p_sdl_get_mouse_click(p_sdl_data *kiosk, SDL_Event *e);
////int p_sdl_clear_screen(p_sdl_data *kiosk);
//int p_sdl_render_string(p_sdl_data *kiosk, char[] string);
//int p_sdl_render_char(p_sdl_data *kiosk, char c);
int p_sdl_set_cursor_x(p_sdl_data *kiosk, int x);
int p_sdl_set_cursor_y(p_sdl_data *kiosk, int y);
//int p_sdl_set_color(p_sdl_data *kiosk, int color);
//
//int p_sdl_draw_line(p_sdl_data *kiosk, int start_x, int start_y, int end_x, int end_y, int stroke_width);
//int p_sdl_draw_rectangle(p_sdl_data *kiosk, int x, int y, int height, int width, int dofill);
//int p_sdl_draw_pixel(p_sdl_data *kiosk, int x. int y);
//int p_sdl_draw_circle(p_sdl_data *kiosk, int x, int y,int radius, int dofill);

/*function p_sdl_new
use to create all the necessary SDL items*/
p_sdl_data * p_sdl_new(void){
	/*create instance of kiosk*/
	p_sdl_data *kiosk;
	kiosk = malloc(sizeof(p_sdl_data));

	/*set window size*/
	kiosk->window_width = 910;
	kiosk->window_height = 400;

	bool success =true;

	/*create window*/
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL could not initialized! SDL_Error: %s\n", SDL_GetError());
		success = false;	
	}
	else{
		kiosk->window = SDL_CreateWindow("Kiosk v0.0.2", 1000, 500, kiosk->window_width, kiosk->window_height,SDL_WINDOW_SHOWN);
		if(kiosk->window ==NULL){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else{
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags)& imgFlags)){
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success =false;
			}
			else{
				kiosk->window_surface = SDL_GetWindowSurface(kiosk->window);
			}
		}
	}

	/*render both screen and keypad to the window */
	if(success){
		/*keypad */
		kiosk->keypad_surface = IMG_Load("/home/quw/miniat_t/peripherals/kiosk/kiosk_keypad/image/keypad.png");

		if(kiosk->keypad_surface ==NULL){
		printf("Unable to load image %s! SDL_Image Error: %s\n", "/home/quw/miniat _k/peripherals/kiosk/image/keypad.png", IMG_GetError());	
		}
		else{
			kiosk->keypad_surface = SDL_ConvertSurface(kiosk->keypad_surface, kiosk->window_surface->format, NULL);
			if(kiosk->keypad_surface ==NULL){
			printf("Unable to optimize image %s! SDL Error: %s\n", "/home/quw/miniat _k/peripherals/kiosk/image/keypad.png", SDL_GetError());	
			}
		}
		if(kiosk->keypad_surface ==NULL){
			success = false;
		}

		/*screen */
		kiosk->screen_surface = IMG_Load("/home/quw/miniat_t/peripherals/kiosk/kiosk_screen/image/screen.png");

		if(kiosk->screen_surface ==NULL){
		printf("Unable to load image %s! SDL_Image Error: %s\n", "/home/quw/miniat_t/peripherals/kiosk/kiosk_screen/image/screen.png", IMG_GetError());	
		}
		else{
			kiosk->screen_surface = SDL_ConvertSurface(kiosk->screen_surface, kiosk->window_surface->format, NULL);
			if(kiosk->screen_surface ==NULL){
			printf("Unable to optimize image %s! SDL Error: %s\n", "/home/quw/miniat_t/peripherals/kiosk/kiosk_screen/image/screen.png", SDL_GetError());	
			}
		}
		if(kiosk->screen_surface ==NULL){
			success = false;
		}

		/*display both screen and keypad*/
		SDL_BlitSurface(kiosk->keypad_surface, NULL, kiosk->window_surface, NULL);

		kiosk->upper_right.x = 300;
		kiosk->upper_right.y = 0;
		kiosk->upper_right.w = 610;
		kiosk->upper_right.h = 400;

		SDL_BlitSurface(kiosk->screen_surface, NULL, kiosk->window_surface, &kiosk->upper_right);

		SDL_UpdateWindowSurface(kiosk->window);

		/*set mouse stat*/


	}
	return kiosk;	
}

/*function p_sdl_close
use to close the sdl library*/
int p_sdl_close(p_sdl_data *kiosk){
	SDL_FreeSurface(kiosk->keypad_surface);
	SDL_FreeSurface(kiosk->screen_surface);

	SDL_DestroyWindow(kiosk->window);
	kiosk->window =NULL;

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
		SDL_GetMouseState(&kiosk->cursor_x, &kiosk->cursor_y);

		if(kiosk->cursor_x <=300 && kiosk->cursor_y<=400){
		c = (kiosk->cursor_x/100+1);
		r = (kiosk->cursor_y/100+4);
		data = ((~((~data)<<c)) ^(~((~data)<<c-1))) | ((~((~data)<<r)) ^(~((~data)<<r-1)));
		return data;
		}
		else{
			return -1;
		}
	}
}

/*function p_sdl_set_cursor_x
use to set the sdl cursor x value to user define value*/
int p_sdl_set_cursor_x(p_sdl_data *kiosk, int x){
	kiosk->cursor_x = x;
	if(kiosk->cursor_x ==x){
		return 0;
	}
	else{
		return 1;
	}
}

/*function p_sdl_set_cursor_y
use to set the sdl cursor y value to user define value*/
int p_sdl_set_cursor_y(p_sdl_data *kiosk, int y){
	kiosk->cursor_y = y;
	if(kiosk->cursor_y ==y){
		return 0;
	}
	else{
		return 1;
	}
}

/*test function*/
int main(int argc, char const *argv[])
{
	p_sdl_data *kiosk;
	int test;
	uint32_t data;
	bool quit;
	SDL_Event e;

	kiosk = p_sdl_new();
	//SDL_Delay(10000);
	//data = p_sdl_get_mouse_click(kiosk);
		test = p_sdl_set_cursor_x(kiosk, 37);
	printf("test is %d\n", test);

	test = p_sdl_set_cursor_y(kiosk, 999);
	printf("test is %d\n", test);

	printf("x is %d and y is %d\n",kiosk->cursor_x, kiosk->cursor_y );

	while(!quit)
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			if(e.type ==SDL_MOUSEBUTTONDOWN){
				data = p_sdl_get_mouse_click(kiosk, &e);
				printf("data is %d\n", data);
			}
			
		}
	}


	test = p_sdl_close(kiosk);

	printf("test is  %d\n", test);
	
	return 0;
}