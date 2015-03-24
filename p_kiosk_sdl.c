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
	SDL_Surface *screen_surface;
	SDL_Surface *test_surface;
	SDL_Surface *keypad_surface;
	SDL_Renderer *renderer;
	SDL_Texture *screen_texture;
	SDL_Texture *keypad_texture;
	int cursor_x;
	int cursor_y;
	SDL_Color color;
}p_sdl_data;

const int S_MIN_X = 324;
const int S_MAX_X = 886;
const int S_MIN_Y = 24;
const int S_MAX_Y = 376;

p_sdl_data * p_sdl_new(void);
//int p_sdl_close(p_sdl_data *kiosk);
uint32_t p_sdl_get_mouse_click(p_sdl_data *kiosk, SDL_Event *e);
//int p_sdl_clear_screen(p_sdl_data *kiosk);
//int p_sdl_render_string(p_sdl_data *kiosk, char[] string);
//int p_sdl_render_char(p_sdl_data *kiosk, char c);
int p_sdl_set_cursor_x(p_sdl_data *kiosk, int x);
int p_sdl_set_cursor_y(p_sdl_data *kiosk, int y);
int p_sdl_set_color(p_sdl_data *kiosk, int color);
//
int p_sdl_draw_line(p_sdl_data *kiosk, int start_x, int start_y, int end_x, int end_y, float stroke_width);
int p_sdl_draw_rectangle(p_sdl_data *kiosk, int x, int y, int height, int width, int dofill);
int p_sdl_draw_pixel(p_sdl_data *kiosk, int x, int y);
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
		kiosk->window = SDL_CreateWindow("Kiosk v0.0.2", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,kiosk->window_width, kiosk->window_height,SDL_WINDOW_SHOWN);
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
		kiosk->keypad_surface = IMG_Load("src/images/keypad.png");
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
		kiosk->screen_surface = IMG_Load("src/images/screen.png");
		if(kiosk->screen_surface ==NULL){
			printf("Unable to load image %s! SDL_Image Error: %s\n", "src/images/keypad.png", IMG_GetError());
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

/*function p_sdl_set_color
use to set the sdl renderer color, default color is black*/
int p_sdl_set_color(p_sdl_data *kiosk, int color){
	switch(color){
		case 0:
			printf("changing color to black\n");
			kiosk->color.r = 0;
			kiosk->color.g = 0;
			kiosk->color.b = 0;
			kiosk->color.a = 255;
			break;
		case 1:
			printf("changing color to blue\n");
			kiosk->color.r = 0;
			kiosk->color.g = 0;
			kiosk->color.b = 255;
			kiosk->color.a = 255;
			break;
		case 2:
			printf("changing color to green\n");
			kiosk->color.r = 0;
			kiosk->color.g = 255;
			kiosk->color.b = 0;
			kiosk->color.a = 255;
			break;
		case 3:
			printf("changing color to red\n");
			kiosk->color.r = 255;
			kiosk->color.g = 0;
			kiosk->color.b = 0;
			kiosk->color.a = 255;
			break;
		case 4:
			printf("changing color to cyan\n");
			kiosk->color.r = 0;
			kiosk->color.g = 255;
			kiosk->color.b = 255;
			kiosk->color.a = 255;
			break;
		case 5:
			printf("changing color to magenta\n");
			kiosk->color.r = 255;
			kiosk->color.g = 0;
			kiosk->color.b = 255;
			kiosk->color.a = 255;
			break;
		case 6:
			printf("changing color to yellow\n");
			kiosk->color.r = 255;
			kiosk->color.g = 255;
			kiosk->color.b = 0;
			kiosk->color.a = 255;
			break;
		case 7:
			printf("changing color to deep sky blue\n");
			kiosk->color.r = 0;
			kiosk->color.g = 191;
			kiosk->color.b = 255;
			kiosk->color.a = 255;
		case 8:
			printf("changing color to deep pink\n");
			kiosk->color.r = 255;
			kiosk->color.g = 20;
			kiosk->color.b = 147;
			kiosk->color.a = 255;
			break;
		case 9:
			printf("changing color to medium spring green\n");
			kiosk->color.r = 0;
			kiosk->color.g = 250;
			kiosk->color.b = 154;
			kiosk->color.a = 255;
			break;
		case 10:
			printf("changing color to purple\n");
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
			return 0;
		}
		return 1;
}

/* function p_sdl_draw_line
use to draw line on the sdl screen*/
int p_sdl_draw_line(p_sdl_data *kiosk, int start_x, int start_y, int end_x, int end_y, float stroke_width){
	if((start_x<S_MIN_X) || (start_x>S_MAX_X) || (start_y <S_MIN_Y) || (start_y > S_MAX_Y)){
		printf("Invalid area to start with !\n");
		return 1;	
	}
	else if ((end_x < S_MIN_X) || (end_x > S_MAX_X) || (end_y < S_MIN_Y) || (end_y> S_MAX_Y)){
		printf("Error, Unable to draw line outside the screen!\n");
		return 1;
	}
	else{
		SDL_SetRenderDrawColor(kiosk->renderer, kiosk->color.r, kiosk->color.g, kiosk->color.b, kiosk->color.a);
		//SDL_RenderSetScale(kiosk->renderer, 1.0, stroke_width);

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
			SDL_SetRenderDrawColor(kiosk->renderer, kiosk->color.r, kiosk->color.g, kiosk->color.b, kiosk->color.a);
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
			SDL_SetRenderDrawColor(kiosk->renderer, kiosk->color.r, kiosk->color.g, kiosk->color.b, kiosk->color.a);
			if(SDL_RenderDrawRect(kiosk->renderer, &outlineRect) !=0){
				printf("fail to draw a rectangle! SDL Error: %s\n", SDL_GetError());
				return 1;
			}
			else{
				SDL_RenderPresent(kiosk->renderer);
				return 0;
			}
		}
	}
}

int p_sdl_draw_pixel(p_sdl_data *kiosk, int x, int y){
	if((x<S_MIN_X) || (x>S_MAX_X) || (y<S_MIN_Y) || (y<S_MAX_Y)){
		printf("Invalid area to start with!\n");
		return 1;
	}
	else{
		SDL_SetRenderDrawColor(kiosk->renderer, kiosk->color.r, kiosk->color.g, kiosk->color.b, kiosk->color.a);
		//SDL_RenderSetScale(kiosk->renderer, 1.0, stroke_width);

		if(SDL_RenderDrawLine(kiosk->renderer, x, y, x+1, y) !=0){
			printf("fail to draw the line! SDL Error: %s\n", SDL_GetError());
			return 1;
		}
		else{
			SDL_RenderPresent(kiosk->renderer);
			return 0;
		}
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
	int color = 0;

	//create new instance of kiosk
	kiosk = p_sdl_new();

	//test function set cursor x
	test = p_sdl_set_cursor_x(kiosk, 37);
	printf("test for the set x functionis %d\n", test);

	//test function set cursor y
	test = p_sdl_set_cursor_y(kiosk, 999);
	printf("test for the set y function is %d\n", test);

	printf("x is %d and y is %d\n",kiosk->cursor_x, kiosk->cursor_y );

	//test the color function
	printf("enter a number from 0-10 to change color\n");
	scanf("%d", &color);
	test = p_sdl_set_color(kiosk, color);
	printf("test for color function is %d\n",test);	

	//test draw line function
	test = p_sdl_draw_line(kiosk, 330, 100, 500, 100, 3.0);
	printf("test for draw function is %d\n", test);

	//test to draw a outlined rect
	test = p_sdl_draw_rectangle(kiosk, 700, 100, 50, 200, 0);
	printf("test for outlined rect is %d\n", test);

	//test to draw a fill rect
	test = p_sdl_draw_rectangle(kiosk, 330, 50, 250, 200, 1);
	printf("test for fill rect is %d\n", test);

	//test to draw a pixel
	test = p_sdl_draw_pixel(kiosk, 700, 300);
	printf("test for draw pixel function is %d\n", test);

	//test the get mouse click function
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
	//test the sdl close function
	test = p_sdl_close(kiosk);

	printf("test for the close functionis  %d\n", test);
	
	return 0;
}
