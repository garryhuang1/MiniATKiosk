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

void failed(int test_number)
{
	printf("\nTest %d failed", test_number);
	getchar();
	exit(1);
}

void assert_int(int test_number, int a, int b)
{
	if (a != b)
		{
			printf("\n%d != %d", a, b);
			failed(test_number);
		}else{
			printf("\n!- assert_num in Test %d passed", test_number);
		}
			
			
}

void assert_null(int test_number, void* a)
{
	if (a == NULL)
		{
			failed(test_number);
		}
}

void test_wait(int test_number)
{
	printf("\n> Finished Test %d", test_number);
	printf("\nPress ENTER to continue");
	getchar();
}



int main ()
{
	int purpose;
	int demo;
	int status= 0;
	SDL_Event e;
	printf("Enter 1 to start the kiosk demo, or 0 to enter test mode\n");
	scanf("%d", &purpose);
	if(purpose == 1){
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
				printf("	6. To render character on the screen\n");
				printf("	7. To render string on the screen\n");
				printf("	8. To get data from the keypad\n");
				printf("	9. To clear the screen\n");
				printf("	0. To exit demo\n");
				scanf("%d", &demo);
				SDL_PollEvent(&e);
	
					switch(demo){
						case 1:{
							int color;
							char check;
							printf("-----------------Color function------------\n");
							printf("Miniat_kiosk allows user to change the color for the render\n");
							printf("Enter from 0 to 10 to change color\n");
							scanf("%d", &color);
							if(p_sdl_set_color(kiosk_demo, color) == 0){
								printf("You have successfully change the color of the renderer\n");
								printf("The renderer will now use this color to render stuff\n");
							}

							SDL_PollEvent(&e);
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
							printf("Miniat_kiosk allows user to draw lines on the screen\n");
							printf("Please enter starting x, startying y, end x and end y with space between them\n");
							scanf("%d %d %d %d", &start_x, &start_y, &end_x, &end_y);
							if(p_sdl_draw_line(kiosk_demo, start_x, start_y, end_x, end_y) == 0){
								printf("You have successfully draw a line at point (%d, %d)\n", start_x, start_y);
							}

							SDL_PollEvent(&e);						
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
						case 3:{
							int x, y, w, h, dofill;
							char check;
							printf("---------------draw rectangle function---------------\n");
							printf("Miniat_kiosk allows user to draw rectangle on the screen with the option to fill it or not\n");
							printf("Please enter x, y, width, and height with space between them\n");
							scanf("%d %d %d %d", &x, &y, &w, &h);
							printf("Please enter 1 if you wish to fill the rectangle and 0 if not\n");
							scanf("%d", &dofill);
							if(p_sdl_draw_rectangle(kiosk_demo, x, y, w, h, dofill) == 0){
								printf("You have successfully draw a rectangle at point (%d, %d)\n", x, y);
							}
							
							SDL_PollEvent(&e);	
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
						case 4:{
							int x, y;
							char check;
							printf("---------------draw pixel function---------------\n");
							printf("Miniat_kiosk allows user to draw pixel on the screen\n");
							printf("Please enter x, and y with space between them\n");
							scanf("%d %d", &x, &y);
							if(p_sdl_draw_pixel(kiosk_demo, x, y) == 0){
								printf("You have successfully draw a pixel at point (%d, %d)\n", x, y);
							}

							SDL_PollEvent(&e);	
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
						case 5:{
							int x, y, r, dofill;
							char check;
							printf("---------------draw circle function---------------\n");
							printf("Miniat_kiosk allows user to draw circle on the screen with the option to fill it or not\n");
							printf("Please enter x, y, and radius with space between them\n");
							scanf("%d %d %d", &x, &y, &r);
							printf("Please enter 1 if you wish to fill the rectangle and 0 if not\n");
							scanf("%d", &dofill);
							if(p_sdl_draw_circle(kiosk_demo, x, y, r, dofill) == 0){
								printf("You have successfully draw a circle at point (%d, %d)\n", x, y);
							}
							
							SDL_PollEvent(&e);	
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
						case 6:{
							char c;
							int x, y, i;
							char check;
							printf("---------------render character function---------------\n");
							printf("Miniat_kiosk allows user to render character on the screen with user define cursor postion\n");
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
							printf("Please enter a character to render\n");
							scanf(" %c", &c);
							if(p_sdl_render_char(kiosk_demo, c) == 0){
								printf("You have successfully render %c on the screen\n", c);
							}
							
							SDL_PollEvent(&e);	
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
						case 7:{
							char s[100];
							int x, y, i;
							char check, temp;
							printf("---------------render string function---------------\n");
							printf("Miniat_kiosk allows user to render string on the screen with user define cursor postion\n");
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
							temp = getchar();
							printf("Please enter a line of string to render\n");
							fgets(s, 100, stdin);
							if(p_sdl_render_string(kiosk_demo, s) == 0){
								printf("You have successfully render %s on the screen\n", s);
							}
							
							SDL_PollEvent(&e);	
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
						case 8:{
							char k;
							uint32_t data;
							char check;
							int temp = 1;
							printf("---------------get mouse data function---------------\n");
							printf("Miniat_kiosk allows user to print out the value from the keypad to screen\n");
	
							printf("Please use mouse to click the button in the keypad area or click close to exit this demo\n");

							while (temp == 1){
								while(SDL_PollEvent(&e) != 0){
									if(e.type == SDL_QUIT){
										temp = 0;
									}
									else if(e.type == SDL_MOUSEBUTTONDOWN){
										data = p_sdl_get_mouse_click(kiosk_demo, &e);
										if (data != -1){
											if(data & (unsigned int)1){
												if(data &(unsigned int)8)
													k = '1';
												else if(data &(unsigned int)16)
													k = '4';
												else if(data &(unsigned int)32)
													k = '7';
												else if(data &(unsigned int)64)
													k = '*';
												else
													printf("fail\n");
											}

											else if(data & (unsigned int)2){
												if(data &(unsigned int)8)
													k = '2';
												else if(data &(unsigned int)16)
													k = '5';
												else if(data &(unsigned int)32)
													k = '8';
												else if(data &(unsigned int)64)
													k = '0';
												else
													printf("fail\n");
											}

											else if(data & (unsigned int)4){
												if(data &(unsigned int)8)
													k = '3';
												else if(data &(unsigned int)16)
													k = '6';
												else if(data &(unsigned int)32)
													k = '9';
												else if(data &(unsigned int)64)
													k = '#';
												else
													printf("fail\n");
											}

											p_sdl_render_char(kiosk_demo, k);
										}
									}	
								}
							}

							SDL_PollEvent(&e);	
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
						case 9:{
							int i;
							char check;
							printf("---------------clear screen function---------------\n");
							printf("Miniat_kiosk allows user to clear the scrren\n");
							printf("Please enter 1 if you wish to clear the screen\n");
							scanf("%d", &i);
							if(i == 1){
								p_sdl_clear_screen(kiosk_demo);
							}

							SDL_PollEvent(&e);	
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
						case 0:{
							EXIT_STATE:
							printf("---------------Exit demo---------------\n");
							printf("Thank you for using Miniat_kiosk!\n");
							p_sdl_close(kiosk_demo);
							status =1;
							break;
						}
					}
				}
			}
		}

	else if(purpose == 0){
		int test_number = 1;
		
		// Test 1 
		p_sdl_data* test_data = p_sdl_new();
	
		assert_null(test_number, test_data);
	
		test_wait(test_number);
	
		/* 
		 * Test 3
		 */
		test_number = 3;
		
		int result_test_3 = p_sdl_render_string(test_data, "Hello World!");
	
		assert_int(test_number, result_test_3, 0);
	
		test_wait(test_number);
		/* 
		 * Test 4
		 */
		test_number = 4;
	
		int result_test_4_x = p_sdl_set_text_cursor_x(test_data, SCREEN_WIDTH / 2);
	
		assert_int(test_number, result_test_4_x, 0);
		assert_int(test_number, p_sdl_get_text_cursor_x(test_data), (SCREEN_WIDTH / 2 )  );
	
		int result_test_4_y = p_sdl_set_text_cursor_y(test_data, SCREEN_HEIGHT / 2 );
	
		assert_int(test_number, result_test_4_y, 0);
		assert_int(test_number, p_sdl_get_text_cursor_y(test_data), SCREEN_HEIGHT / 2);
	
		int result_test_4_p = p_sdl_render_string(test_data, "Center");
	
		assert_int(test_number, result_test_4_p, 0);
	
		test_wait(test_number);
		/* 
		 * Test 5
		 */
		test_number = 5;
	
		int result_test_5 = p_sdl_clear_screen(test_data);
		
		assert_int(test_number, result_test_5, 0);
	
		test_wait(test_number);
		/* 
		 * Test 6
		 */
		test_number = 6;
	
		int result_test_6_x = p_sdl_set_text_cursor_x(test_data, 0);
		assert_int(test_number, result_test_6_x, 0);
	
		int result_test_6_y = p_sdl_set_text_cursor_y(test_data, 0);
		assert_int(test_number, result_test_6_y, 0);
	
		int result_test_6_char = p_sdl_render_char(test_data, 'a');
	
		assert_int(test_number, result_test_6_char, 0);
		assert_int(test_number, p_sdl_get_text_cursor_x(test_data), 0 + CURSOR_MOVE);
	
		test_wait(test_number);
		/* 
		 * Test 7
		 */
		test_number = 7;
	
		int result_test_7_clear = p_sdl_clear_screen(test_data);
		assert_int(test_number, result_test_7_clear, 0);
	
		int result_test_7_x = p_sdl_set_text_cursor_x(test_data, 0);
		assert_int(test_number, result_test_7_x, 0);
	
		int result_test_7_y = p_sdl_set_text_cursor_y(test_data, 0);
		assert_int(test_number, result_test_7_y, 0);
	
		int result_test_7_color = p_sdl_set_color(test_data, 3);
		assert_int(test_number, result_test_7_color, 0);
		assert_int(test_number, p_sdl_get_color(test_data), 3);
	
		int result_test_7_print = p_sdl_render_string(test_data, "Hello World!");
		assert_int(test_number, result_test_7_print, 0);
	
		test_wait(test_number);
		/* 
		 * Test 12
		 */
		test_number = 12;
	 
		int result_test_12_color = p_sdl_set_color(test_data, 0);
		assert_int(test_number, result_test_12_color, 0);
	
		int result_test_12_pixel = p_sdl_draw_pixel(test_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		assert_int(test_number, result_test_12_pixel, 0);
	
		test_wait(test_number);
		/* 
		 * Test 13
		 */
	
		test_number = 13;
	
		// Test 13.1
	
		int result_test_13_1_draw = p_sdl_draw_rectangle(test_data, 0, 0, 50, 50, 0);
		assert_int(test_number, result_test_13_1_draw, 0);
	
		test_wait(test_number);
	
		int result_test_13_1_draw2 = p_sdl_draw_rectangle(test_data, 0, 0, 50, 50, 1);
		assert_int(test_number, result_test_13_1_draw2, 0);
	
		test_wait(test_number);
	
		// Test 13.2
		int result_test_13_2_clear = p_sdl_clear_screen(test_data);
		assert_int(test_number, result_test_13_2_clear, 0);
	
		int result_test_13_2_draw = p_sdl_draw_rectangle(test_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, 50, 0);
		assert_int(test_number, result_test_13_2_draw, 0);
	
		test_wait(test_number);
	
		int result_test_13_2_draw2 = p_sdl_draw_rectangle(test_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, 50, 1);
		assert_int(test_number, result_test_13_2_draw2, 0);
	
		test_wait(test_number);
	
		/* 
		 * Test 14
		 */
		test_number = 14;
	
		int result_test_14_clear = p_sdl_clear_screen(test_data);
		assert_int(test_number, result_test_14_clear, 0);
	
		int result_test_14_draw = p_sdl_draw_line(test_data, 50, 50, 100, 100);
		assert_int(test_number, result_test_14_draw, 0);
	
		test_wait(test_number);
	
		/* 
		 * Test 15
		 */
		test_number = 15;
	
		int result_test_15_clear = p_sdl_clear_screen(test_data);
		assert_int(test_number, result_test_15_clear, 0);
	
		int result_test_15_draw = p_sdl_draw_circle(test_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 0);
		assert_int(test_number, result_test_15_draw, 0);
	
		test_wait(test_number);
	
		int result_test_15_draw2 = p_sdl_draw_circle(test_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 1);
		assert_int(test_number, result_test_15_draw2, 0);
	
		test_wait(test_number);
	
		// Test 20
		test_number = 20;
		
		int result_test_20 = p_sdl_close(test_data);
	
		assert_int(test_number, result_test_20, 0);
	}
}
