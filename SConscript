Import('*')
import os

SDL2_CFLAGS = str.split(os.popen('sdl2-config --cflags').read())
SDL2_LIBS = str.split(os.popen('sdl2-config --libs').read())

INC = [ '#/vm/inc', '#/system/kiosk' ]

LIBS = [ 'libminiat', 'libSDL2_ttf', 'libSDL2_image', 'libSDL2_gfx' ]

KIOSK_CFLAGS = []
KIOSK_LIBPATH = str.split(env[ 'LIBPATH' ])

for flag in SDL2_CFLAGS:
	if flag.startswith("-I"):
		INC.append(flag[2:])
	else:
		KIOSK_CFLAGS.append(flag)

for flag in SDL2_LIBS:
	if flag.startswith("-L"):
		KIOSK_LIBPATH.append(flag[2:])
	else:
		LIBS.append(flag[2:])

buildSharedLibrary("kiosk_sdl", "p_kiosk_sdl.c", CPPPATH=INC, LIBS=LIBS, CFLAGS=KIOSK_CFLAGS, LIBPATH=KIOSK_LIBPATH)
buildSharedLibrary("kiosk_screen", "p_kiosk_screen.c", CPPPATH=INC, LIBS=LIBS, CFLAGS=KIOSK_CFLAGS, LIBPATH=KIOSK_LIBPATH)
buildSharedLibrary("kiosk_keypad", "p_kiosk_keypad.c", CPPPATH=INC, LIBS=LIBS, CFLAGS=KIOSK_CFLAGS, LIBPATH=KIOSK_LIBPATH)
buildSharedLibrary("kiosk_print_screen", "p_kiosk_print_screen.c", CPPPATH = INC, LIBS = LIBS, CFLAGS=KIOSK_CFLAGS, LIBPATH=KIOSK_LIBPATH)