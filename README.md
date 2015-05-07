# MiniAT Kiosk
MiniAT Kiosk provides a method to replicate the functionality of a physical kiosk in MiniAT.

MiniAT Kiosk provides the following peripherals:

* Screen
* Keypad
* Receipt Printer

## Installation

Installation to an installation of MiniAT is simple. 

1. Install dependencies: sdl2, sdl2-ttf, sdl2-image and sdl2-gfx

	For Ubuntu, run `apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-gfx-dev'

2. Clone this repository to the `system` directory of MiniAT

	`git clone https://bitbucket.org/miniat_amos/kiosk.git`

3. Run `scons` in the root directory of MiniAT.

## Demos

MiniAT Kiosk comes with a number of demo MiniAT assembly programs. The demo assembly is available in `asm/` directory of the kiosk directory. 

The MiniAT system program is available at `out/exe/miniat_kiosk`.

To run an assembly program, run like so:

` ./out/exe/miniat_kiosk ./out/bin/(bin file name)`

Or you can update your runtime path and library first by using the following two commands:

	`export PATH=$PATH:~/miniat/out/exe`

	`export LD_LIBRARY_PATH=~/miniat/out/lib`

Then you can simply run the program in the following way:
	
	`miniat_kiosk ./out/bin/(bin file name)`

There are a number of assembly programs available to pass to the system program:

* `test_all.bin`: Demos usage of all peripherals
* `test_draw_screen.bin`: Demos usage of drawing on the screen
* `test_keypad_1.bin`: Demos using the keypad and printing it to the screen
* `test_printer_1.bin`: Demos basic usage of the receipt printer
* `test_printer_2.bin`: Demos usage of the receipt printer
* `test_printer_3.bin`: Demos usage of the receipt printer
* `test_screen.bin`: Demos basic usage of the screen
* `test_screen_char.bin`:  Demos printing characters individually to the screen 
* `test_screen_color.bin`: Demos changing the color of the font
* `test_screen_draw2.bin`: Demos drawing a square that movies across the screen
* `test_screen_draw.bin`: Demos drawing a line to the screen
* `test_screen_move.bin`: Demos writing to the screen at an offset
* `test_screen_string2.bin`: Demos writing to the screen
* `test_screen_string3.bin`: Demos writing to the screen
* `test_screen_string.bin`: Demos writing to the screen
* `test_screen_string_wait.bin`: Demos writing to the screen after waiting
* `keypad_test.bin`: Demos keypad


