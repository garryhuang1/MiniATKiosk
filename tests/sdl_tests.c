#include <stdio.h>

#include "p_kiosk_sdl.h"

#define WINDOW_HEIGHT 410
#define WINDOW_WIDTH 640
#define CURSOR_MOVE 12

void failed(int test_number)
{
	printf("Test %d failed", test_number);
	getchar();
	exit(1)
}

void assert_int(int test_number, int a, int b)
{
	if (a != b)
		{
			failed(test_number);
		}
}

void assert_null(int test_number, void* a)
{
	if (a == NULL)
		{
			failed(test_number);
		}
}

void wait()
{
	printf("Press ENTER to continue");
	getchar();
}


int test_number = 1;


// Test 1 
p_sdl_data* test = p_sdl_new();

assert_null(1, p_sdl_data);

wait();

// Test 2.1
test_number = 2;

int result_test_2 = -999;

while (result_test_2 != -1)
	{
		result_test_2 = p_sdl_get_mouse_click(p_sdl_data);
	}

wait();

// Test 2.2
result_test_2 = -999;

// convert here

while (result_test_2 != 1)
	{
		result_test_2 = p_sdl_get_mouse_click(p_sdl_data);
	}

wait();
/* 
 * Test 3
 */
test_number = 3;

int result_test_3 = p_sdl_render_string(p_sdl_data, "Hello World!");

assert_int(test_number, result_test_3, 0);

wait();
/* 
 * Test 4
 */
test_number = 4;

int result_test_4_x = p_sdl_set_cursor_x(p_sdl_data, SCREEN_WIDTH / 2);

assert_int(test_number, result_test_4_x, 0);
assert_int(test_number, p_sdl_get_cursor_x(p_sdl_data), SCREEN_WIDTH / 2);

int result_test_4_y = p_sdl_set_cursor_y(p_sdl_data, SCREEN_HEIGHT / 2);

assert_int(test_number, result_test_4_y, 0);
assert_int(test_number, p_sdl_get_cursor_y(p_sdl_data), SCREEN_HEIGHT / 2);

int result_test_4_p = p_sdl_render_string(p_sdl_data, "Center");

assert_int(test_number, result_test_4_p, 0);

wait();
/* 
 * Test 5
 */
test_number = 5;

int result_test_5 = p_sdl_clear_screen(p_sdl_data);

assert_int(test_number, result_test_5, 0);

wait();
/* 
 * Test 6
 */
test_number = 6;

int result_test_6_x = p_sdl_set_cursor_x(p_sdl_data, 0);
assert_int(test_number, result_test_6_x, 0);

int result_test_6_y = p_sdl_set_cursor_y(p_sdl_data, 0);
assert_int(test_number, result_test_6_y, 0);

int result_test_6_char = p_sdl_render_char(p_sdl_data, 'a');

assert_int(test_number, result_test_6_char, 0);
assert_int(test_number, p_sdl_get_cursor_x(p_sdl_data), 0 + CURSOR_MOVE);

wait();
/* 
 * Test 7
 */
test_number = 7;

int result_test_7_clear = p_sdl_clear_screen(p_sdl_data);
assert_int(test_number, result_test_7_clear, 0);

int result_test_7_x = p_sdl_set_cursor_x(p_sdl_data, 0);
assert_int(test_number, result_test_7_x, 0);

int result_test_7_y = p_sdl_set_cursor_y(p_sdl_data, 0);
assert_int(test_number, result_test_7_y, 0);

int result_test_7_color = p_sdl_set_color(p_sdl_data, 3);
assert_int(test_number, result_test_7_color, 3);

int result_test_7_print = p_sdl_render_string(p_sdl_data, "Hello World!");
assert_int(test_number, result_test_7_print, 0);

wait();
/* 
 * Test 8
 */
test_number = 8;

int result_test_8_clear = p_sdl_clear_screen(p_sdl_data);
assert_int(test_number, result_test_8_clear, 0);

int result_test_8_init = p_sdl_set_cursor_x(p_sdl_data, 5);
assert_int(test_number, result_test_8_init, 0);

// Set invalid values
int result_test_8_x = p_sdl_set_cursor_x(p_sdl_data, 1000);
assert_int(test_number, result_test_8_x, 1);

int result_test_8_y = p_sdl_set_cursor_y(p_sdl_data, 1000);
assert_int(test_number, result_test_8_y, 1);

assert_int(test_number, p_sdl_get_cursor_x(p_sdl_data), 5);

int result_test_8_x = p_sdl_set_cursor_x(p_sdl_data, -3);
assert_int(test_number, result_test_8_x, 1);

int result_test_8_y = p_sdl_set_cursor_y(p_sdl_data, -1);
assert_int(test_number, result_test_8_y, 1);

assert_int(test_number, p_sdl_get_cursor_x(p_sdl_data), 5);

wait();
/* 
 * Test 9
 */
test_number = 9;

p_sdl_data->cursor_x = 599;
p_sdl_data->cursor_y = 409;

int result_test_9_print = p_sdl_render_string(p_sdl_data, "Hello World!");
assert_int(test_number, result_test_9_print, 1);

p_sdl_data->cursor_x = 0;
p_sdl_data->cursor_y = 0;

wait();
/* 
 * Test 10
 */
test_number = 10;

int result_test_10 = p_sdl_set_color(p_sdl_data, 99);
assert_int(test_number, result_test_10, 1);


assert_int(test_number, p_sdl_get_color(p_sdl_data), 3);

int result_test_10_print = p_sdl_render_string(p_sdl_data, "Hello World!");
assert_int(test_number, result_test_10_print, 0);

wait();
/* 
 * Test 11
 */
test_number = 11;

p_sdl_data->color = 99

int result_test_11_print = p_sdl_draw_pixel(p_sdl_data, );
assert_int(test_number, result_test_11_print, 0);

assert_int(test_number, p_sdl_get_color(p_sdl_data), 0);

wait();
/* 
 * Test 12
 */
test_number = 12;

int result_test_12_color = p_sdl_set_color(p_sdl_data, 0);
assert_int(test_number, result_test_12_color, 0);

int result_test_12_pixel = p_sdl_draw_pixel(p_sdl_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
assert_int(test_number, result_test_12_pixel, 0);

wait();
/* 
 * Test 13
 */

test_number = 13;

// Test 13.1

int result_test_13_1_draw = p_sdl_draw_rectangle(p_sdl_data, 0, 0, 50, 50, 0);
assert_int(test_number, result_test_13_1_draw, 0);

wait();

int result_test_13_1_draw2 = p_sdl_draw_rectangle(p_sdl_data, 0, 0, 50, 50, 1);
assert_int(test_number, result_test_13_1_draw2, 0);

wait();

// Test 13.2
int result_test_13_2_clear = p_sdl_clear_screen(p_sdl_data);
assert_int(test_number, result_test_13_2_clear, 0);

int result_test_13_2_draw = p_sdl_draw_rectangle(p_sdl_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, 50, 0);
assert_int(test_number, result_test_13_2_draw, 0);

wait();

int result_test_13_2_draw2 = p_sdl_draw_rectangle(p_sdl_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, 50, 1);
assert_int(test_number, result_test_13_2_draw2, 0);

wait();

/* 
 * Test 14
 */
test_number = 14;

int result_test_14_clear = p_sdl_clear_screen(p_sdl_data);
assert_int(test_number, result_test_14_clear, 0);

int result_test_14_draw = p_sdl_draw_line(p_sdl_data, 50, 50, 100, 100);
assert_int(test_number, result_test_14_draw, 0);

wait();

/* 
 * Test 15
 */
test_number = 15;

int result_test_15_clear = p_sdl_clear_screen(p_sdl_data);
assert_int(test_number, result_test_15_clear, 0);

int result_test_15_draw = p_sdl_draw_circle(p_sdl_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 0);
assert_int(test_number, result_test_15_draw, 0);

wait();

int result_test_15_draw2 = p_sdl_draw_circle(p_sdl_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 1);
assert_int(test_number, result_test_15_draw2, 0);

wait();

/* 
 * Test 16
 */
test_number = 16;

int result_test_16_clear = p_sdl_clear_screen(p_sdl_data);
assert_int(test_number, result_test_16_clear, 0);

// Set color to blue
int result_test_16_color = p_sdl_set_color(p_sdl_data, 1);
assert_int(test_number, result_test_16_color, 0);

int result_test_16_pixel = p_sdl_draw_pixel(p_sdl_data, 641, 411);
assert_int(test_number, result_test_16_pixel, 1);

wait();


/* 
 * Test 17
 */
test_number = 17;
 
 
int result_test_17_clear = p_sdl_clear_screen(p_sdl_data);
assert_int(test_number, result_test_17_clear, 0);

int result_test_17_draw = p_sdl_draw_rectangle(p_sdl_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1000, 1000, 0);
assert_int(test_number, result_test_17_draw, 1);

wait();

int result_test_17_draw2 = p_sdl_draw_rectangle(p_sdl_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1000, 1000, 1);
assert_int(test_number, result_test_17_draw2, 1);

wait();

/* 
 * Test 18
 */

test_number = 18;

int result_test_18_clear = p_sdl_clear_screen(p_sdl_data);
assert_int(test_number, result_test_18_clear, 0);

int result_test_18_draw = p_sdl_draw_line(p_sdl_data, -1, 50, 700, 100);
assert_int(test_number, result_test_18_draw, 1);

/* 
 * Test 19
 */

test_number = 19;

int result_test_19_draw = p_sdl_draw_circle(p_sdl_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 0);
assert_int(test_number, result_test_19_draw, 0);

wait();

int result_test_19_draw2 = p_sdl_draw_circle(p_sdl_data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 1);
assert_int(test_number, result_test_19_draw2, 0);

wait();



// Test 20
int result_test_20 = p_sdl_close(p_sdl_data);

assert_int(test_number, result_test_20, 0);
