/*
 * sdl_screen_writer.c
 *
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
 *  Function Prototypes
 */
int screen_writer_init();
int screen_writer_push(uint32_t data);
char screen_writer_keypad_parser(uint32_t mask);
int screen_writer_pop();
void screen_writer_error_handler(unsigned short error_code);
/*
 * TODO: create buffer_clear function
 */


/*
 *  Error code value constants
 */
const unsigned short MISSING_COLUMN_ERROR = 0;
const unsigned short MISSING_ROW_ERROR = 1;
const unsigned short KEYPAD_PARSER_NULL_ERROR = 2;
const unsigned short BUFFER_FULL_ERROR = 3;
const unsigned short POPPING_EMPTY_BUFFER_ERROR = 4;

/*
 *  Global Variables
 */
int buffer_pos = 0;
char buffer[51];
char* tail;
char* head;
char* pos;

int screen_writer_init() {
	int success = 1;
	tail = &buffer[0];
	head = &buffer[50];
	pos = &buffer[50];

	return success;
}

int screen_writer_push(uint32_t data) {
	int success = 1;
	char input;

	input = screen_writer_keypad_parser(data);

	if (input == ' ') {
		success = -1;
		screen_writer_error_handler(KEYPAD_PARSER_NULL_ERROR);
	}

	if (success > 0) {
	    
		if (buffer_pos >= sizeof(buffer) {
			success = -1;
			screen_writer_error_handler(BUFFER_FULL_ERROR);
		}
	  
		else {
			buffer[buffer_pos] = input, buffer_pos++;
		}
	}
	return success;
}

char screen_writer_keypad_parser(uint32_t mask) {
	mask = mask << 25;
	mask = mask >> 25;

	if (mask & (unsigned int)1) {

		if (mask & (unsigned int)8) {
			return '1';
		}
		else if (mask & (unsigned int)16) {
			return '4';
		}
		else if (mask & (unsigned int)32) {
			return '7';
		}
		else if (mask & (unsigned int)64) {
			return '#';
		}
		else {
			screen_writer_error_handler(MISSING_ROW_ERROR);
		}
	}

	else if (mask & (unsigned int)2) {
		if (mask & (unsigned int)8) {
			return '2';
		}
		else if (mask & (unsigned int)16) {
			return '5';
		}
		else if (mask & (unsigned int)32) {
			return '8';
		}
		else if (mask & (unsigned int)64) {
			return '0';
		}
		else {
			screen_writer_error_handler(MISSING_ROW_ERROR);
		}
	}

	else if (mask & (unsigned int)4) {
		if (mask & (unsigned int)8) {
			return '3';
		}
		else if (mask & (unsigned int)16) {
			return '6';
		}
		else if (mask & (unsigned int)32) {
			return '9';
		}
		else if (mask & (unsigned int)64) {
			return '#';
		}
		else {
			screen_writer_error_handler(MISSING_ROW_ERROR);
		}
	}

	else {
		screen_writer_error_handler(MISSING_COLUMN_ERROR);
	}

	return ' ';
}

int screen_writer_pop() {
	int success = 1;
	buffer_pos--;
	
	if (buffer_pos < 0) {
		buffer_pos++; 
		success = -1;
		screen_writer_error_handler(POPPING_EMPTY_BUFFER_ERROR);  
	}  
	else {
		buffer[buffer_pos] = NULL; // not sure if NULL works; if not use ""   
	}
	
	return success;
}

void screen_writer_error_handler(unsigned short error_code) {
	switch (error_code) {
		case 0:
			fputs("Error! Missing keypad column value!\n", stderr);
			break;
		case 1:
			fputs("Error! Missing keypad row value!\n", stderr);
			break;
		case 2:
			fputs("Error! Keypad value parser returned NULL!\n", stderr);
			break;
		case 3: 
			fputs("Error! Character buffer full!\n", stderr);
			break;
		case 4: 
			fputs("Error! Cannot pop an empty buffer!\n" stderr);
			break;
		default:
			fputs("Error! Error Handler initiated without valid error code!\n", stderr);
			break;
	}
}
