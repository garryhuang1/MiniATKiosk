/*
 * File: sdl_demo.c
 * 
 * This is a stripped down version of the test
 * program for demo purposes.
 * 
 * WARNING: Repeating Yourself Here!
 */
#include <stdio.h>
#include <string.h>

#include "p_kiosk_sdl.h"
#include <SDL2/SDL.h>

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 610
#define CURSOR_MOVE 12

int main ()
{
	int demo;
	int status= 0;
	SDL_Event e;

	p_sdl_data* kiosk_demo = p_sdl_new();
	printf("Welcome to Miniat_kiosk!\n"); 
	printf("This demo program will show you what you can do with our kiosk program\n");
	while((status == 0) && (SDL_PollEvent(&e))){
		printf("status = %d\n", status);
		if(e.type == SDL_QUIT)
			status = 1;
		else{		
			printf("Please enter one of the following number to see the demo:\n");
			printf("	1. To change the color of render\n");
			printf("	2. To draw a line on the screen\n");
			printf("	3. To draw a rectangle on the screen\n");
			printf("	4. To draw a pixel on the screen\n");
			printf("	5. To draw a circle on the screen\n");
			printf("	6. To render a character on the screen\n");
			printf("	7. To render a string on the screen\n");
			printf("	8. To get data from the keypad\n");
			printf("	9. To clear the screen\n");
			printf("	0. To exit demo\n");
			scanf("%d", &demo);
			p_sdl_get_event(kiosk_demo);

				switch(demo){
					case 1:{
						int color;
						char check;
						printf("-----------------Color function------------\n");
						printf("Miniat_kiosk allows users to change the color for the render\n");
						printf("Enter from 0 to 10 to change color\n");
						scanf("%d", &color);
						if(p_sdl_set_color(kiosk_demo, color) == 0){
							printf("You have successfully changed the color of the renderer\n");
							printf("The renderer will now use this color to render stuff\n");
						}
						p_sdl_get_event(kiosk_demo);
						printf("Would you like see another demo? y/n\n");
						scanf(" %c", &check);
						if(check == 'n'){
							goto EXIT_STATE;
							break;
						}
						else if (check == 'y'){
							break;
						}
						else{
							printf("Error input\n");
							status = 1;
							break;
						}
					}
					case 2:{
						int start_x, end_x;
						int start_y, end_y;
						char check;
						printf("---------------draw line function---------------\n");
						printf("Miniat_kiosk allows users to draw lines on the screen\n");
						printf("Please enter starting x, starting y, end x and end y with space between them\n");
						scanf("%d %d %d %d", &start_x, &start_y, &end_x, &end_y);
						if(p_sdl_draw_line(kiosk_demo, start_x, start_y, end_x, end_y) == 0){
							printf("You have successfully draw a line at point (%d, %d)\n", start_x, start_y);
						}
						p_sdl_get_event(kiosk_demo);						
						printf("Would you like too see another demo? y/n\n");
						scanf(" %c", &check);
						if(check == 'n'){
							goto EXIT_STATE;
							break;
						}
						else if (check == 'y'){
							break;
						}
						else{
							printf("Error input\n");
							status = 1;
							break;
						}
					}
					case 3:{
						int x, y, w, h, dofill;
						char check;
						printf("---------------draw rectangle function---------------\n");
						printf("Miniat_kiosk allows users to draw a rectangle on the screen with the option to fill it or not\n");
						printf("Please enter x, y, width, and height with space between them\n");
						scanf("%d %d %d %d", &x, &y, &w, &h);
						printf("Please enter 1 if you wish to fill the rectangle and 0 if not\n");
						scanf("%d", &dofill);
						if(p_sdl_draw_rectangle(kiosk_demo, x, y, w, h, dofill) == 0){
							printf("You have successfully draw a rectangle at point (%d, %d)\n", x, y);
						}
						
						p_sdl_get_event(kiosk_demo);	
						printf("Would you like to see another demo? y/n\n");
						scanf(" %c", &check);
						if(check == 'n'){
							goto EXIT_STATE;
							break;
						}
						else if (check == 'y'){
							break;
						}
						else{
							printf("Error input\n");
							status = 1;
							break;
						}
					}
					case 4:{
						int x, y;
						char check;
						printf("---------------draw pixel function---------------\n");
						printf("Miniat_kiosk allows users to draw pixel on the screen\n");
						printf("Please enter x, and y with space between them\n");
						scanf("%d %d", &x, &y);
						if(p_sdl_draw_pixel(kiosk_demo, x, y) == 0){
							printf("You have successfully draw a pixel at point (%d, %d)\n", x, y);
						}
						p_sdl_get_event(kiosk_demo);	
						printf("Would you like to see another demo? y/n\n");
						scanf(" %c", &check);
						if(check == 'n'){
							goto EXIT_STATE;
							break;
						}
						else if (check == 'y'){
							break;
						}
						else{
							printf("Error input\n");
							status = 1;
							break;
						}
					}
					case 5:{
						int x, y, r, dofill;
						char check;
						printf("---------------draw circle function---------------\n");
						printf("Miniat_kiosk allows users to draw circle on the screen with the option to fill it or not\n");
						printf("Please enter x, y, and radius with space between them\n");
						scanf("%d %d %d", &x, &y, &r);
						printf("Please enter 1 if you wish to fill the rectangle and 0 if not\n");
						scanf("%d", &dofill);
						if(p_sdl_draw_circle(kiosk_demo, x, y, r, dofill) == 0){
							printf("You have successfully draw a circle at point (%d, %d)\n", x, y);
						}
						
						p_sdl_get_event(kiosk_demo);	
						printf("Would you like to see another demo? y/n\n");
						scanf(" %c", &check);
						if(check == 'n'){
							goto EXIT_STATE;
							break;
						}
						else if (check == 'y'){
							break;
						}
						else{
							printf("Error input\n");
							status = 1;
							break;
						}
					}
					case 6:{
						char c;
						int x, y, i;
						char check;
						printf("---------------render character function---------------\n");
						printf("Miniat_kiosk allows users to render character on the screen with user define cursor postion\n");
						printf("Please enter 1 if you wish to define where to render the character, or 0 to default\n");
						scanf("%d", &i);
						if(i == 1){
							printf("Please enter x and y with space between them\n");
							scanf("%d %d", &x, &y);
							if((p_sdl_set_text_cursor_x(kiosk_demo, x)==0) &&(p_sdl_set_text_cursor_y(kiosk_demo, y) == 0)){
								printf("You have successfully change the text cursor to (%d, %d)\n",kiosk_demo->text_cursor_x, kiosk_demo->text_cursor_y );
							}
						}
						else if(i = 0){}
						//scanf("%c", &c);
						printf("Please enter a character to render\n");
						
						scanf(" %c", &c);
						if(p_sdl_render_char(kiosk_demo, c) == 0){
							printf("You have successfully rendered %c on the screen\n", c);
						}
						
						p_sdl_get_event(kiosk_demo);	
						printf("Would you like to see another demo? y/n\n");
						scanf(" %c", &check);
						if(check == 'n'){
							goto EXIT_STATE;
							break;
						}
						else if (check == 'y'){
							break;
						}
						else{
							printf("Error input\n");
							status = 1;
							break;
						}
					}
					case 7:{
						char s[100];
						int x, y, i;
						char check, temp;
						printf("---------------render string function---------------\n");
						printf("Miniat_kiosk allows users to render string on the screen with user define cursor postion\n");
						printf("Please enter 1 if you wish to define where to render the character, or 0 to default\n");
						scanf("%d", &i);
						if(i == 1){
							printf("Please enter x and y with a space between them\n");
							scanf("%d %d", &x, &y);
							if((p_sdl_set_text_cursor_x(kiosk_demo, x)==0) &&(p_sdl_set_text_cursor_y(kiosk_demo, y) == 0)){
								printf("You have successfully change the text cursor to (%d, %d)\n",kiosk_demo->text_cursor_x, kiosk_demo->text_cursor_y );
							}
						}
						else if(i = 0){}
						temp = getchar();
						printf("Please enter a line of string to render\n");
						fgets(s, 100, stdin);
						if(p_sdl_render_string(kiosk_demo, s) == 0){
							printf("You have successfully rendered %s on the screen\n", s);
						}
						
						p_sdl_get_event(kiosk_demo);	
						printf("Would you like to see another demo? y/n\n");
						scanf(" %c", &check);
						if(check == 'n'){
							goto EXIT_STATE;
							break;
						}
						else if (check == 'y'){
							break;
						}
						else{
							printf("Error input\n");
							status = 1;
							break;
						}
					}	
					case 8:{
						char k;
						uint32_t data;
						char check;
						int temp = 1;
						printf("---------------get mouse data function---------------\n");
						printf("Miniat_kiosk allows users to print out the value from the keypad to screen\n");

						printf("Please use the mouse to click the button in the keypad area or click close to exit this demo\n");
						while (temp == 1){
							while(p_sdl_get_event(kiosk_demo) != 1){
								if(kiosk_demo->mouse_event.type == SDL_QUIT){
									temp = 0;
								}
								else if(kiosk_demo->mouse_event.type == SDL_MOUSEBUTTONDOWN){
									data = p_sdl_get_mouse_click(kiosk_demo);
									printf("data is %d\n",data );
									if (data > 0){
										switch(data){
										case 9: //1
											data = data + 40;
											break;
										case 10: //2
											data = data + 40;
											break;
										case 12: //3
											data = data + 39;
											break;
										case 17: //4
											data = data + 35;
											break;
										case 18: //5
											data = data + 35;
											break;
										case 20: //6
											data = data + 34;
											break;
										case 33: //7
											data = data + 22;
											break;
										case 34: //8
											data = data + 22;
											break;
										case 36: //9
											data = data + 21;
											break;
										case 65: //*
											data = data - 23;
											break;
										case 66: //0
											data = data - 18;
											break;
										case 68: //#
											data = data - 33;
											break;
										}
						
										}	
										else if (data == 0){
											data = 0;
										}
										printf("data is %d\n", data);		
										p_sdl_render_char(kiosk_demo, data);
									}
									
							}
						}
						p_sdl_get_event(kiosk_demo);	
						printf("Would you like to see another demo? y/n\n");
						scanf(" %c", &check);
						if(check == 'n'){
							goto EXIT_STATE;
							break;
						}
						else if (check == 'y'){
							break;
						}
						else{
							printf("Error input\n");
							status = 1;
							break;
						}
					}
					case 9:{
						int i;
						char check;
						printf("---------------clear screen function---------------\n");
						printf("Miniat_kiosk allows users to clear the scrren\n");
						printf("Please enter 1 if you wish to clear the screen\n");
						scanf("%d", &i);
						if(i == 1){
							p_sdl_clear_screen(kiosk_demo);
						}
						p_sdl_get_event(kiosk_demo);	
						printf("Would you like to see another demo? y/n\n");
						scanf(" %c", &check);
						if(check == 'n'){
							goto EXIT_STATE;
							break;
						}
						else if (check == 'y'){
							break;
						}
						else{
							printf("Error input\n");
							status = 1;
							break;
						}
					}	
					case 0:{
						EXIT_STATE:
						printf("---------------Exit demo---------------\n");
						printf("Thank you for using the Miniat_kiosk!\n");
						p_sdl_close(kiosk_demo);
						status =1;
						break;
					}
			}
		}
	}
}