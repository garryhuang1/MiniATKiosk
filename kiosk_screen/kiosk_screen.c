#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <miniat/miniat.h>
#include "kiosk_screen.h"

struct p_kiosk_screen {
	int connected;
	m_uword screen_address;
	m_bus *screen_bus;
};

 
p_kiosk_screen* p_kiosk_screen_new(m_uword screen_address){
	
}
	
void p_kiosk_screen_free(p_kiosk_screen *d) {

}


void p_kiosk_screen_clock(p_kiosk_screen *d) {
	
}


m_bus p_kiosk_screen_get_bus(p_kiosk_screen *t){
	
}


void p_kiosk_screen_set_bus(p_kiosk_screen *t, m_bus bus) {
	
}

