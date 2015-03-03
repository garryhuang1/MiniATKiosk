#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <miniat/miniat.h>
#include "kiosk_screen.h"
#include "SDL2/SDL.h"
#include "sdl_screen_renderer.h"

struct p_kiosk_screen {
	m_uword screen_command_address;
	m_uword screen_char_address;
	m_uword screen_x_address;
	m_uword screen_y_address;
	m_uword screen_color_address;
	m_bus *screen_bus;
	/* Storage */
	char screen_buffer[51];
	int buffer_loc;
	short int x_pos;
	short int y_pos;
	short int color;
};

 
p_kiosk_screen* p_kiosk_screen_new(	m_uword screen_command_address, 	
									m_uword screen_char_address, 
									m_uword screen_x_address, 
									m_uword screen_y_address, 
									m_uword screen_color_address){	
										
	p_kiosk_screen *s = malloc(sizeof(p_kiosk_screen));
	
	
	
	if(s) {
		s->screen_bus = (m_bus *)malloc(sizeof(m_bus));
		if(!s->screen_bus) {
			free(s);
			s = NULL;
		} else {
			s->screen_command_address = screen_command_address;
			s->screen_char_address = screen_char_address;
			s->screen_x_address = screen_x_address;
			s->screen_y_address = screen_y_address;
			s->screen_color_address = screen_color_address;
			s->buffer_loc = 0;
			s->x_pos = 0;
			s->y_pos = 0;
			s->color = 0;
			
			screen_init(610, 400, "/home/jacob/Downloads/screen.png");
			
		}
		
	}
	return s;
	
}
	
void p_kiosk_screen_free(p_kiosk_screen *s) {
	if(s) {
		screen_close();
		
		free(s);
		
	}
	return;
}


void p_kiosk_screen_clock(p_kiosk_screen *s) {
	if (s->screen_bus->address == s->screen_command_address) {
			
	} else if (s->screen_bus->address == s->screen_char_address) {
		
	} else if (s->screen_bus->address == s->screen_x_address) {
		
	} else if (s->screen_bus->address == s->screen_y_address) {
		
	} else if (s->screen_bus->address == s->screen_color_address) {
		
	}
}

m_bus p_kiosk_screen_get_bus(p_kiosk_screen *s){
	m_bus b = { 0 };
	if(!s) {
		return b;
	}
	return *(s->screen_bus);
}

void p_kiosk_screen_set_bus(p_kiosk_screen *s, m_bus bus) {
	if(s) {
		memcpy(s->screen_bus, &bus, sizeof(bus));
	}
}

