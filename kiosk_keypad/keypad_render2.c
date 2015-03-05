#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "keypad_render2.h"

const int KEYPAD_WIDTH = 300;
const int KEYPAD_HEIGHT = 400;

/*SDL surface*/
SDL_Window * window =NULL;
SDL_Surface* window_surface = NULL;
SDL_Surface* keypad = NULL;
SDL_Rect upper_right;

#define BUTTON_ROW 4
#define BUTTON_COL 3

const int BUTTON_WIDH = 100;
const int BUTTON_HEIGHT = 100;

/*button define*/
typedef struct{
	SDL_Point mPosition;
	char number;
}Button;

Button kBUTTON[BUTTON_ROW][BUTTON_COL];

/*main SDL functions*/
bool loadButton();
int keypad_init();
SDL_Surface* load_media();
void closeWindow();

/*button functions*/
void setPostion(int y, int x, int row, int col, int k);
void eventHandle(SDL_Event *e);

/*
 *Sets the positions of the buttons
 *as well as assigns ascii values to the buttons.
*/
void setButtStat(int y, int x, int row, int col, int k){
	kBUTTON[row][col].mPosition.x = x;
	kBUTTON[row][col].mPosition.y = y;

	if(k<10){
		kBUTTON[row][col].number = k+48;
	}

	else if (k==10){
		kBUTTON[row][col].number = k+32;
	}
	else if (k==11){
		kBUTTON[row][col].number = k+37;
	}
	else if (k==12){
		kBUTTON[row][col].number = k+23;
	}
}

int keypad_init(){
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		window = SDL_CreateWindow("Keypad v0.0.1", 1000,500, KEYPAD_WIDTH, KEYPAD_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)){
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else{
				window_surface = SDL_GetWindowSurface(window);
			}
		}

	}

	if(success)
	{
		keypad = load_media();
	}

	SDL_BlitSurface(keypad, NULL, window_surface, NULL);

	SDL_UpdateWindowSurface(window);

	if(!loadButton()){
		printf("Failed to load buttons\n");
		success = false;
	}

	if(success){
		return 1;
	}
	else{
		return -1;
	}

}

/*Loads keypad image*/
SDL_Surface* load_media() {
	SDL_Surface* optimized_surface = NULL;

	SDL_Surface* loaded_surface = IMG_Load("/home/quw/miniat_t/peripherals/kiosk/kiosk_keypad/image/keypad.png");
	if (loaded_surface == NULL){
		printf("Unable to load image %s! SDL_Image Error: %s\n", "/home/quw/miniat _k/peripherals/kiosk/image/keypad.png", IMG_GetError());
	}
	else{
		optimized_surface = SDL_ConvertSurface(loaded_surface, window_surface->format, NULL);
		if (optimized_surface == NULL){
			printf("Unable to optimize image %s! SDL Error: %s\n", "/home/quw/miniat _k/peripherals/kiosk/image/keypad.png", SDL_GetError());
		
		}

		SDL_FreeSurface(loaded_surface);
	}

	return optimized_surface;
}
/*Sets the location of the buttons row by row.*/
bool loadButton(){
	int k = 1;
	int i, j; //i = col, j = row
	bool success = true; 
	
	if(keypad =NULL){
		printf("Failed to load keypad!\n");
		success = false;
	}
	
	else{
		for(i =0; i<4; i++){
			for(j = 0; j<3; j++){
				setButtStat(i*100, j*100, i, j,k);
				k++;
			}
		}

	}
	

	return success;
}
/*Closes the window*/
void closeWindow(){
	SDL_FreeSurface(keypad);

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}
