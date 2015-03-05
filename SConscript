Import('*')

INC = [ '#/vm/inc', '#/peripherals/simple_term',]

LIBS = [ 'libminiat', 'libkiosk_screen', 'libkeypad_read', 'libsdl_screen_renderer', 'libkiosk_keypad', 'libkeypad_render', "SDL2", "libSDL2_image", 'libsimple_term']

buildProgram("test", "test.c", CPPPATH=INC, LIBS=LIBS)
buildMash('nothing.asm')




