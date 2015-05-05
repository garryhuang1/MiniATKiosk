#include <stdio.h>
#include <stdlib.h>

#include <miniat/miniat.h>
#include "p_kiosk_print_screen.h"
#include "p_kiosk_sdl.h"

p_kiosk_print_screen* p_kiosk_print_screen_new(p_sdl_data* init_struct, m_uword print_screen_address) {
	p_kiosk_print_screen *p = malloc(sizeof(p_kiosk_print_screen));

	if (p) {
		p->bus = (m_bus *)malloc(sizeof(m_bus));
		if (!p->bus) {
			free(p);
			p = NULL;
		}
		else {
			p->print_screen_start_address = print_screen_address;
			p->sdl_struct = init_struct;
			p->connected = 0;
		}
	}
 
	return p;
}
void p_kiosk_print_screen_free(p_kiosk_print_screen *p) {
	
  
	if (p) {
		if (!p->connected) {
			free (p->bus);
		}
		free(p);
	}
	
	return;
}
void p_kiosk_print_screen_clock(p_kiosk_print_screen *p) {
  
	m_uword command_address = p->print_screen_start_address;
	m_uword add_char_address = p->print_screen_start_address+1;
	m_uword print_char_address = p->print_screen_start_address+2;
	m_uword x_loc_address = p->print_screen_start_address+3;
	m_uword y_loc_address = p->print_screen_start_address+4;
	m_uword wait_address = p->print_screen_start_address+5;
	
	int result = 1;
	
	if(p->bus->address == command_address) {
		 if(p->bus->rW == M_HIGH) {
			if(p->bus->req && !p->bus->ack) {
				switch (p->bus->data){
					case COMMAND_PRINT_NEW_LINE:
						  result = p_sdl_receipt_printer_new_line(p->sdl_struct);
						  break;
					case COMMAND_CUT_RECEIPT:
						  result = p_sdl_receipt_cut(p->sdl_struct);
						  break;
					  default:
						  result = 1;
				}
			p->bus->ack = M_HIGH;
			}
			else if (p->bus->ack == M_HIGH) {
				p->bus->ack = M_LOW;
			}
		 }
		 else if(p->bus->rW == M_LOW){
		    if (p->bus->req && !p->bus->ack){
		    }
		    else if(p->bus->ack == M_HIGH){
			  p->bus->ack = M_LOW;
		    }
		}
	}
	else if(p->bus->address == add_char_address) {
		if(p->bus->rW == M_HIGH) {
			if (p->bus->req && !p->bus->ack) {
				p->character = p->bus->data;
				
				p->bus->ack = M_HIGH;
			}
			else if (p->bus->ack == M_HIGH) {
				p->bus->ack = M_LOW;
			}
		}
		else if(p->bus->rW == M_LOW){
		    if (p->bus->req && !p->bus->ack){
		    }
		    else if(p->bus->ack == M_HIGH){
			  p->bus->ack = M_LOW;
		    }
		 }
	}
	else if (p->bus->address == print_char_address) {
		if(p->bus->rW == M_HIGH) {
			if (p->bus->req && !p->bus->ack) {
			      int result = p_sdl_receipt_render_char(p->sdl_struct, p->bus->data);
			      
			      p->bus->ack = M_HIGH;
			}
			else if (p->bus->ack == M_HIGH) {
			      p->bus->ack = M_LOW;
			}
		}
		else if(p->bus->rW == M_LOW){
		    if (p->bus->req && !p->bus->ack){
		    }
		    else if(p->bus->ack == M_HIGH){
			  p->bus->ack = M_LOW;
		    }
		}
	}
	else if (p->bus->address == x_loc_address) {
		if(p->bus->rW == M_HIGH) {
			if (p->bus->req && !p->bus->ack) {
			    int result = p_sdl_set_receipt_cursor_x(p->sdl_struct, p->bus->data);
			    p->bus->ack = M_HIGH;
			}
			else if (p->bus->ack == M_HIGH) {
			      p->bus->ack = M_LOW;
			}
		}
		if(p->bus->rW == M_LOW) {
		      if (p->bus->req && !p->bus->ack) {
			   p->bus->data = p_sdl_get_receipt_cursor_x(p->sdl_struct);
		      }
		      else if (p->bus->ack == M_HIGH){
			   p->bus->ack = M_LOW;
		      }
		}
	}
	else if (p->bus->address == y_loc_address) {
		if(p->bus->rW == M_HIGH) {
			if (p->bus->req && !p->bus->ack) {
			    int result = p_sdl_set_receipt_cursor_y(p->sdl_struct, p->bus->data);
			    p->bus->ack = M_HIGH;
			}
			else if (p->bus->ack == M_HIGH) {
			      p->bus->ack = M_LOW;
			}
		}
		if(p->bus->rW == M_LOW) {
		      if (p->bus->req && !p->bus->ack) {
			   p->bus->data = p_sdl_get_receipt_cursor_y(p->sdl_struct);
		      }
		      else if (p->bus->ack == M_HIGH){
			   p->bus->ack = M_LOW;
		      }
		}
	}
	else if (p->bus->address == wait_address) {
	      if(p->bus->rW == M_HIGH) {
		    if(p->bus->req && !p->bus->ack) {
			  int time = p->bus->data;
			  sleep(time);
			  p->bus->ack = M_HIGH;
		    }
		    else if(p->bus->ack == M_HIGH) {
			  p->bus->ack == M_LOW;
		    }
	      }
	     else if(p->bus->rW == M_LOW){
		    if (p->bus->req && !p->bus->ack){
		    }
		    else if(p->bus->ack == M_HIGH){
			  p->bus->ack = M_LOW;
		    }
	     }
	}		    		  
}  
m_bus p_kiosk_print_screen_get_bus(p_kiosk_print_screen *p) {
	
	m_bus empty_bus = { 0 } ;
	
	if (!p) {
		 return empty_bus;
	}
	return *(p->bus);
}
void p_kiosk_print_screen_set_bus(p_kiosk_print_screen *p, m_bus bus) {

	if (p) {
		memcpy(p->bus, &bus, sizeof(bus));
	}
}