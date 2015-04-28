#include <stdio.h>

#include "p_kiosk_sdl.h"

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 610
#define CURSOR_MOVE 14

/*
 * There functions are for asserting test results and managing errors
 */
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

	// Test 2.1
	test_number = 2; 

	int result_test_2 = 0;

	while (result_test_2 == 0)
		{
			result_test_2 = p_sdl_get_mouse_click(test_data);
			printf("result is %d\n", result_test_2);
		}

	test_wait(test_number);

	// Test 2.2
	result_test_2 = 0;

	// convert here 

	while (result_test_2 == 0)
		{
			result_test_2 = p_sdl_get_mouse_click(test_data);
			printf("result is %d\n", result_test_2);
		}

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

	int result_test_4_x = p_sdl_set_text_cursor_x(test_data, (SCREEN_WIDTH / 2 ));

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
	 * Test 8
	 */
	test_number = 8;

	int result_test_8_clear = p_sdl_clear_screen(test_data);
	assert_int(test_number, result_test_8_clear, 0);

	int result_test_8_init = p_sdl_set_text_cursor_x(test_data, 5);
	assert_int(test_number, result_test_8_init, 0);
 
	// Set invalid values
	int result_test_8_x = p_sdl_set_text_cursor_x(test_data, 1000);
	assert_int(test_number, result_test_8_x, 1);

	int result_test_8_y = p_sdl_set_text_cursor_y(test_data, 1000);
	assert_int(test_number, result_test_8_y, 1);

	assert_int(test_number, p_sdl_get_text_cursor_x(test_data), 5);

	result_test_8_x = p_sdl_set_text_cursor_x(test_data, -3);
	assert_int(test_number, result_test_8_x, 1);

	result_test_8_y = p_sdl_set_text_cursor_y(test_data, -1);
	assert_int(test_number, result_test_8_y, 1);

	assert_int(test_number, p_sdl_get_text_cursor_x(test_data), 5);

	test_wait(test_number);
	/* 
	 * Test 9
	 */
	test_number = 9;

	test_data->text_cursor_x = 320;
	test_data->text_cursor_y = 29;

	int result_test_9_print = p_sdl_render_string(test_data, "1Hello World!");
	assert_int(test_number, result_test_9_print, 1);
	
	test_data->text_cursor_x = 885;
	test_data->text_cursor_y = 29;

	int result_test_9_print2 = p_sdl_render_string(test_data, "2Hello World!");
	assert_int(test_number, result_test_9_print2, 1);

	int result_test_9_print3 = p_sdl_reset(test_data); 
	assert_int(test_number, result_test_9_print3, 0);
	
	
	assert_int(test_number, p_sdl_get_color(test_data), 0);
	assert_int(test_number, p_sdl_get_text_cursor_x(test_data), 0 );
	assert_int(test_number, p_sdl_get_text_cursor_y(test_data), 0 );

	
	
	test_wait(test_number);
	/* 
	 * Test 10
	 */
	test_number = 10;

	int result_test_10 = p_sdl_set_color(test_data, 99);
	assert_int(test_number, result_test_10, 1);
	
	assert_int(test_number, p_sdl_get_color(test_data), 0);

	int result_test_10_print = p_sdl_render_string(test_data, "Hello World!");
	
	assert_int(test_number, result_test_10_print, 0);

	test_wait(test_number);
	/* 
	 * Test 11
	 */
	test_number = 11;
 
	//test_data->color = 99;

	//int result_test_11_print = p_sdl_render_string(test_data, "Hello World!");
	//assert_int(test_number, result_test_11_print, 0);

	//assert_int(test_number, p_sdl_get_color(test_data), 0);

	p_sdl_reset(test_data);

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

	/* 
	 * Test 16
	 */
	test_number = 16;

	int result_test_16_clear = p_sdl_clear_screen(test_data);
	assert_int(test_number, result_test_16_clear, 0);

	// Set color to blue
	int result_test_16_color = p_sdl_set_color(test_data, 1);
	assert_int(test_number, result_test_16_color, 0);

	int result_test_16_pixel = p_sdl_draw_pixel(test_data, 641, 411);
	assert_int(test_number, result_test_16_pixel, 1);

	test_wait(test_number);


	/* 
	 * Test 17
	 */
	test_number = 17;
	 
	int result_test_17_clear = p_sdl_clear_screen(test_data);
	assert_int(test_number, result_test_17_clear, 0);

	int result_test_17_draw = p_sdl_draw_rectangle(test_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1000, 1000, 0);
	assert_int(test_number, result_test_17_draw, 1);

	test_wait(test_number);

	int result_test_17_draw2 = p_sdl_draw_rectangle(test_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1000, 1000, 1);
	assert_int(test_number, result_test_17_draw2, 1);

	test_wait(test_number);

	/* 
	 * Test 18
	 */

	test_number = 18;

	int result_test_18_clear = p_sdl_clear_screen(test_data);
	assert_int(test_number, result_test_18_clear, 0);

	int result_test_18_draw = p_sdl_draw_line(test_data, -1, 50, 700, 100);
	assert_int(test_number, result_test_18_draw, 1);

	/* 
	 * Test 19
	 */

	test_number = 19;

	int result_test_19_draw = p_sdl_draw_circle(test_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 500, 0);
	assert_int(test_number, result_test_19_draw, 1);

	test_wait(test_number);

	int result_test_19_draw2 = p_sdl_draw_circle(test_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 500, 1);
	assert_int(test_number, result_test_19_draw2, 1);

	test_wait(test_number);

	/* 
	 * Test 20
	 */
	test_number = 20;

	int result_test_20_print = p_sdl_render_string(test_data, "A Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long Long String");
	assert_int(test_number, result_test_20_print, 1); 
	
	/* 
	 * Test 21
	 */
	test_number = 21;
	
	int result_test_21_color = p_sdl_set_color(test_data, 3);
	assert_int(test_number, result_test_21_color, 0);
	assert_int(test_number, p_sdl_get_color(test_data), 3);
	
	int t = 0;
	int final = 0;
	
	for (t = 0; t < 150; t++)
		{
			int temp = 0;
			temp = p_sdl_render_char(test_data, 'a');
			final = temp | final;
		}
	
	assert_int(test_number, final, 0); 
	

	test_wait(test_number);

	/* 
	 * Test 22
	 */
	test_number = 22;
	
	int result_test_22 = p_sdl_get_receipt_cursor_x(test_data);
	assert_int(test_number, result_test_22, 0); 
	
	
	test_wait(test_number);

	/* 
	 * Test 23
	 */
	test_number = 23;
	
	int result_test_23 = p_sdl_get_receipt_cursor_y(test_data);
	assert_int(test_number, result_test_23, 0); 
	
	
	test_wait(test_number);

	/* 
	 * Test 24
	 */
	test_number = 24;
	
	int result_test_24_print = p_sdl_receipt_render_char(test_data, 'a');
	assert_int(test_number, result_test_24_print, 0); 
	
	test_wait(test_number);

	/* 
	 * Test 25
	 */
	test_number = 25;
	
	int t_25 = 0;
	int final_25 = 0;
	
	for (t = 0; t < 20; t++)
		{
			int temp_25 = 0;
			temp_25 = p_sdl_receipt_render_char(test_data, 'l');
			final_25 = temp_25 | final_25;
		}
	
	assert_int(test_number, final_25, 0); 
	
	
	test_wait(test_number);
	
	/* 
	 * Test 26
	 */
	test_number = 26;
	
	int result_test_26 = p_sdl_receipt_printer_new_line(test_data);
	assert_int(test_number, result_test_26, 0); 
	
	test_wait(test_number); 
	

	/* 
	 * Test 27
	 */
	test_number = 27;
	
	int result_test_27 = p_sdl_set_receipt_cursor_x(test_data, 30);
	assert_int(test_number, result_test_27, 0);
	 assert_int(test_number, p_sdl_get_receipt_cursor_x(test_data), 30);
	
	test_wait(test_number);


	/* 
	 * Test 28
	 */
	test_number = 28;
	
	int result_test_28 = p_sdl_set_receipt_cursor_y(test_data, 30);
	assert_int(test_number, result_test_28, 0);
	assert_int(test_number, p_sdl_get_receipt_cursor_y(test_data), 30);
	
	test_wait(test_number);
	
	/* 
	 * Test 29
	 */
	test_number = 29;
	
	int result_test_29 = p_sdl_receipt_render_char(test_data, 'b');
	assert_int(test_number, result_test_29, 0);
	
	test_wait(test_number);

	/* 
	 * Test 30
	 */
	test_number = 30;
	
	int result_test_30 = p_sdl_receipt_cut(test_data);
	assert_int(test_number, result_test_30, 0);
	
	test_wait(test_number);

	// Close Test
	test_number += 1;
	
	int result_test_20 = p_sdl_close(test_data);

	assert_int(test_number, result_test_20, 0);
}
