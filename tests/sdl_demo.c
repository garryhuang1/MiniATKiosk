/*
 * File: sdl_demo.c
 * 
 * This is a stripped down version of the test
 * program for demo purposes.
 * 
 * WARNING: Repeating Yourself Here!
 */
#include <stdio.h>

#include "p_kiosk_sdl.h"

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
