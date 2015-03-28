#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

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
	SDL_Rect text_space;
	TTF_Font *text_font;
	SDL_Texture *pixel_texture;
	int cursor_x;
	int cursor_y;
	int font_size;
	int text_cursor_x;
	int text_cursor_y;
	int text_line_size;
	SDL_Color color;
}p_sdl_data;

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
int p_sdl_set_cursor_x(p_sdl_data *kiosk, int x);
int p_sdl_set_cursor_y(p_sdl_data *kiosk, int y);
int p_sdl_set_color(p_sdl_data *kiosk, int color);
int p_sdl_draw_line(p_sdl_data *kiosk, int start_x, int start_y, int end_x, int end_y, int color);
int p_sdl_draw_rectangle(p_sdl_data *kiosk, int x, int y, int height, int width, int dofill, int color);
int p_sdl_draw_pixel(p_sdl_data *kiosk, int x, int y, int color);
int p_sdl_draw_circle(p_sdl_data *kiosk, int x, int y,int radius, int dofill, int color);

/*function p_sdl_new
use to create all the necessary SDL items*/
p_sdl_data * p_sdl_new(void){
	/*create instance of kiosk*/
	p_sdl_data *kiosk;
	kiosk = malloc(sizeof(p_sdl_data));

	/*set window size*/
	kiosk->window_width = 910;
	kiosk->window_height = 400;

	/*set default font size*/
	kiosk->font_size = 12;

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
		kiosk->text_font = TTF_OpenFont("src/fonts/pt_sans_regular.ttf", kiosk->font_size);

		if (kiosk->text_font == NULL) {
			printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		}
	}

	/* Default color settings to black*/
	if (kiosk->color.r == NULL || kiosk->color.g == NULL || kiosk->color.b == NULL) {
		kiosk->color.r = 0;
		kiosk->color.g = 0;
		kiosk->color.b = 0;
	}
	
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
			return 0;
		}
		SDL_SetRenderDrawColor(kiosk->renderer, kiosk->color.r, kiosk->color.g, kiosk->color.b, kiosk->color.a);
		
		return 1;
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
	}
}

/* function p_sdl_draw_line
use to draw line on the sdl screen*/
int p_sdl_draw_line(p_sdl_data *kiosk, int start_x, int start_y, int end_x, int end_y, int color){
	if((start_x<S_MIN_X) || (start_x>S_MAX_X) || (start_y <S_MIN_Y) || (start_y > S_MAX_Y)){
		printf("Invalid area to start with !\n");
		return 1;	
	}
	else if ((end_x < S_MIN_X) || (end_x > S_MAX_X) || (end_y < S_MIN_Y) || (end_y> S_MAX_Y)){
		printf("Error, Unable to draw line outside the screen!\n");
		return 1;
	}
	else{
		p_sdl_set_color(kiosk,color);
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
int p_sdl_draw_rectangle(p_sdl_data *kiosk, int x, int y, int height, int width, int dofill, int color){
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
			p_sdl_set_color(kiosk,color);
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
			p_sdl_set_color(kiosk,color);
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
int p_sdl_draw_pixel(p_sdl_data *kiosk, int x, int y, int color){
	if((x<S_MIN_X) || (x>S_MAX_X) || (y<S_MIN_Y) || (y>S_MAX_Y)){
		printf("Invalid area to start with! x is: %d and y is: %d\n", x, y);
		return 1;
	}
	else{
		p_sdl_set_color(kiosk,color);
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
int p_sdl_draw_circle(p_sdl_data *kiosk, int x, int y,int radius, int dofill, int color){
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
			p_sdl_set_color(kiosk, color);

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
			p_sdl_set_color(kiosk, color);
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

/*test function*/
int main(int argc, char const *argv[])
{
	p_sdl_data *kiosk;
	int test;
	uint32_t data;
	char test_string[12] = "Hello World";
	char test_char = '!';
	char whitespace = ' ';
	bool quit;
	SDL_Event e;
	int color = 0;
	int i = 0;
	int trash;
	int temp;

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
	test = p_sdl_draw_line(kiosk, 330, 100, 500, 100, 0);
	printf("test for draw function is %d\n", test);

	//test to draw a outlined rect
	test = p_sdl_draw_rectangle(kiosk, 600, 100, 50, 200, 0, 1);
	printf("test for outlined rect is %d\n", test);

	//test to draw a fill rect
	test = p_sdl_draw_rectangle(kiosk, 500, 50, 250, 200, 1, 2);
	printf("test for fill rect is %d\n", test);

	//test to draw a pixel
	test = p_sdl_draw_pixel(kiosk, 700, 350, 3);
	printf("test for draw pixel function is %d\n", test);

	//test tp draw a filled circle
	test = p_sdl_draw_circle(kiosk, 600, 200, 100, 1, 1);
	printf("test for draw filled circle is %d\n", test);
	// Test to render string(s)
	i = 0;
	for (i; i < 5; i++) {
		//test to render string
		test = p_sdl_render_string(kiosk, test_string);
		trash = p_sdl_render_char(kiosk, whitespace);
	}
		printf("test for render string is %d\n", test);

	//test to draw a outlined circle
	test = p_sdl_draw_circle(kiosk, 500, 150, 100, 0, 3);
	printf("test for draw outlined circle is %d\n", test);


	printf("enter 1 if you want to clear the screen\n");
	scanf("%d",&temp);
	if(temp ==1){
		test = p_sdl_clear_screen(kiosk);
		printf("test for clear screen function is %d\n", test);
	//test to render character(s)
	i = 0;
	for (i; i < 70; i++) {
		test = p_sdl_render_char(kiosk, test_char);
	}
	printf("test for render char is %d\n", test);

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
