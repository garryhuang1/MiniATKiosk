#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <miniat/miniat.h>
#include "kiosk.h"
#include "p_kiosk_sdl.h"

struct kiosk{
	int connected;
	m_uword r_address;
	m_uword w_address;
	m_bus *r_bus;
	m_bus *w_bus;
	p_sdl_data *k_sdl;
};

kiosk * p_kiosk_new(m_uword R_address, m_uword W_address){
	kiosk *k = malloc(sizeof(kiosk));
	if(k){
		k->r_bus = (m_bus *)malloc(sizeof(m_bus));
		k->w_bus = (m_bus *)malloc(sizeof(m_bus));
		if(!k->r_bus || ! k->w_bus){
			free(k);
			k = NULL;
		}
		else{
			k->connected = 0;
			k->r_address = R_address;
			k->w_address = W_address;

			k->k_sdl = p_sdl_new();

		}
	}
	return k;
}

//void p_kiosk_bus_connector_set(kiosk *k, m_bus *bus){
//	if(k && bus){
//		if(!k->connected){
//			free(k->bus);
//		}
//		k->bus = bus;
//		k->connected = 1;
//	}
//	return;
//}

void p_kiosk_free(kiosk *k){
	if(k){
		if(!k->connected){
			free(k->r_bus);
			free(k->w_bus);
		}
		free(k);
	}
	return;
}

void p_kiosk_read_clock(kiosk *k, SDL_Event *e){
	uint32_t data;
	printf("in read clock\n");
	if(!k){
		return;
	}
	printf("pass !k\n");

	if(k->r_bus->req && (k->r_bus->address == k->r_address) && !k->r_bus->rW && !k->r_bus->ack){
		printf("in here\n");
		k->r_bus->ack = M_HIGH;
		data = p_sdl_get_mouse_click(k->k_sdl, e);
		k->r_bus->data = data;
	}
	else if(k->r_bus->ack && (k->r_bus->address == k->r_address)){
		k->r_bus->ack = M_LOW;
	}
	printf("fail\n");
	return;
}

void p_kiosk_write_clock(kiosk *k){
	char c;
	printf("in write clock\n");

	if(!k){
		return;
	}

	if(k->w_bus->req && (k->w_bus->address == k->w_address) && k->w_bus->rW && !k->w_bus->ack){
		k->w_bus->ack = M_HIGH;
		if (k->w_bus->data & (unsigned int)1) {

			if (k->w_bus->data & (unsigned int)8) {
				c = '1';
			}
			else if (k->w_bus->data & (unsigned int)16) {
				c = '4';
			}
			else if (k->w_bus->data & (unsigned int)32) {
				c = '7';
			}
			else if (k->w_bus->data & (unsigned int)64) {
				c = '#';
			}
			else {
				printf("fail\n");
			}
		}
	
		else if (k->w_bus->data & (unsigned int)2) {
			if (k->w_bus->data & (unsigned int)8) {
				c = '2';
			}
			else if (k->w_bus->data & (unsigned int)16) {
				c = '5';
			}
			else if (k->w_bus->data & (unsigned int)32) {
				c = '8';
			}
			else if (k->w_bus->data & (unsigned int)64) {
				c = '0';
			}
			else {
				printf("fail\n");
			}
		}
	
		else if (k->w_bus->data & (unsigned int)4) {
			if (k->w_bus->data & (unsigned int)8) {
				c = '3';
			}
			else if (k->w_bus->data & (unsigned int)16) {
				c = '6';
			}
			else if (k->w_bus->data & (unsigned int)32) {
				c = '9';
			}
			else if (k->w_bus->data & (unsigned int)64) {
				c = '#';
			}
			else {
				printf("fail\n");
			}
		}

		p_sdl_render_char(k->k_sdl, 'c');
	}

	else if ((k->w_bus->address == k->w_address) && k->w_bus->ack){
		k->w_bus->ack = M_LOW;
	}
	return;
}

m_bus p_kiosk_get_read_bus(kiosk *k){
	m_bus b = {0};
	if(!k){
		return b;
	}
	return *(k->r_bus);
}

m_bus p_kiosk_get_write_bus(kiosk *k){
	m_bus b = {0};
	if(!k){
		return b;
	}
	return *(k->w_bus);
}

void p_kiosk_set_read_bus(kiosk *k, m_bus bus){
	if(k){
		memcpy(k->r_bus, &bus, sizeof(bus));
	}
}

void p_kiosk_set_write_bus(kiosk *k, m_bus bus){
	if(k){
		memcpy(k->w_bus, &bus, sizeof(bus));
	}
}