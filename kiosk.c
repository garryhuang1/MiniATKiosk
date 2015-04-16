#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "miniat/miniat.h"
#include "p_kiosk_sdl.h"

#define MINIAT_LOG_FILENAME "miniat.log"

#define P_KEYPAD 0x4030
#define P_SCREEN 0x4012 

miniat *m = NULL;
p_kiosk_keypad *k = NULL;
p_kiosk_screen *s = NULL;

static void cleanup();

int main(int argc, char *argv[]){
  m_bus bus_state;
  m_bus peripheral_bus_state;

  FILE *f = fopen(*argv[1], "rb");

  m = miniat_new(f);

  k = p_kiosk_keypad_new(P_KEYPAD);
  s = p_kiosk_screen_new(P_SCREEN);

  while(1){
    miniat_clock(m);
    
    bus_state = miniat_pins_bus_get(m);
    
    p_kiosk_keypad_set_bus(k, bus_state);
    p_kiosk_screen_set_bus(s, bus_state);
    
    p_kiosk_keypad_clock(k);
    p_kiosk_screen_clock(s);
    
    peripheral_bus_state = p_kiosk_keypad_get_bus(k);
    if(peripheral_bus_state.address == P_KEYPAD){
      miniat_pins_bus_set(m, peripheral_bus_state);
      continue;
    }
    
    peripheral_bus_state = p_kiosk_screen_get_bus(s);
    if(peripheral_bus_state.address == P_SCREEN){
      miniat_pins_bus_set(m, peripheral_bus_state);
      continue;
    }
  }
}

static void cleanup(){
   if(m){
     miniat_free(m);
   }
   if(k){
     p_kiosk_keypad_free(k);
   }
   if(s){
     p_kiosk_screen_free(s);
   }
}