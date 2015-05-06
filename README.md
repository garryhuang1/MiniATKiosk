# README 
MiniAT Kiosk provides a method to replicate the functionality of a physical kiosk in MiniAT.

MiniAT Kiosk provides the following peripherals:

* Screen
* Keypad
* Receipt Printer

# Installation

Installation is simple. 

1. Clone this repository to the /system directory of MiniAT

`git clone https://bitbucket.org/miniat_amos/kiosk.git`
2. Run `scons` in the root directory of MiniAT.

# Demos

MiniAT Kiosk comes with a number of demo system programs and MiniAT assembly programs. The code for the system programs are located in `tests/` and the demo assembly is available in `asm/`. 

Compiled versions are in `./out/exe/`

* `test_both`: Uses screen and keypad
* `test_all`: Uses all peripherals
* `test_screen`: Uses the screen peripheral

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


# Tests

To run MiniAT tests on the SDL frontend library, execute `./out/exe/sdl_test` from the MiniAT root directory

