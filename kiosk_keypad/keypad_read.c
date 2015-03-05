#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


int keypad_read_init();
uint32_t keypad_read_getdata(SDL_Event *e);

int keypad_read_init(){
	int success =1;


	return success;
}

uint32_t keypad_read_getdata(SDL_Event *e){
	int success = 1;
	uint32_t data = 0x00000000;
	int c,r;
	char temp;

	if(e -> type == SDL_MOUSEBUTTONDOWN){
		int x, y;
		SDL_GetMouseState(&x, &y);

		c = (x/100+1);
		r = (y/100+4);

		data = ((~((~data)<<c)) ^(~((~data)<<c-1))) | ((~((~data)<<r)) ^(~((~data)<<r-1)));

		printf("the column is %d, and the row is %d\n", c, r);
		return data;

	}
}