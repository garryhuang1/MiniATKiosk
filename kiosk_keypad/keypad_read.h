#ifndef KEYPAD_READ_H_
#define KEYPAD_READ_H_

extern int keypad_read_init();

extern uint32_t keypad_read_getdata(SDL_Event *e);

#endif /* KEYPAD_READ_H_ */