Import('*')

INC = [ '#/vm/inc', '#/peripherals/simple_term',]

LIBS = [ 'libminiat', 'libkiosk_screen', 'libsdl_screen_renderer', "SDL2", "libSDL2_image", 'libsimple_term']

buildProgram("test_screen", "test_screen.c", CPPPATH=INC, LIBS=LIBS)
buildMash('nothing.asm')

