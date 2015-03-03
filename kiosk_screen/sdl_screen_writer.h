/*
 * sdl_screen_writer.h
 *
 */

#ifndef SDL_SCREEN_WRITER_H_
#define SDL_SCREEN_WRITER_H_

extern int screen_writer_init();
/*
 *   Initializes assets used by the screen writer. This includes the character buffer and buffer tail, head, and current position.
 *   Parameters: None
 *   Returns: int (negative, if unsuccessful / positive, if successful)
 */

extern int screen_writer_push(uint32_t data);
/*
 *   Pushes a character onto the character buffer and advances position by 1 if position not equal to tail
 *   Parameters: uint32_t unsigned 32-bit integer
 *   Returns: int (negative, if unsuccessful / positive, if successful)
 */

extern char screen_writer_keypad_parser(uint32_t data);
/*
 *   Determines matrix keypad value that was entered and returns it as a character
 *   Parameter: uint32_t unsigned 32-bit integer
 *   Returns: char
 */

extern int screen_writer_pop();
/*
 *   Removes first character in the queue
 *   Parameters: None
 *   Returns: int (negative, if unsuccessful / positive, if successful)
 */

extern int screen_writer_render();
/*
 *   Renders values in character buffer queue onto the screen
 *   Parameters: None
 *   Returns: int (negative, if unsuccessful / positive, if successful)
 */

extern void screen_writer_error_handler(unsigned short error_code);
/*
 *   Reports any errors passed to it via standard error
 *   Parameters: unsigned short error code constant
 *   Returns: None
 */

#endif /* SDL_SCREEN_WRITER_H_ */
