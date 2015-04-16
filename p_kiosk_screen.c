#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <miniat/miniat.h>
#include "p_kiosk_screen.h"
#include "p_kiosk_sdl.h"



 
p_kiosk_screen* p_kiosk_screen_new(p_sdl_data* init_struct, m_uword screen_start_address){	
										
	p_kiosk_screen *s = malloc(sizeof(p_kiosk_screen));
	

	if(s) {
		s->screen_bus = (m_bus *)malloc(sizeof(m_bus));
		if(!s->screen_bus) {
			free(s);
			s = NULL;
		} else {
			s->screen_start_address = screen_start_address;
			s->sdl_struct = init_struct;
			s->string_buffer_location = 0;
			s->drawmode = DRAWMODE_PIXEL;
			int last_status = 0;
			s->draw_buffer[0] = 0;
			s->draw_buffer[1] = 0;
			s->draw_buffer[2] = 0;
			s->draw_buffer[3] = 0;
			s->draw_buffer[4] = 0;
			s->string_buffer[0] = '\0';
		}
		
	}
	return s;
	
}
	
void p_kiosk_screen_free(p_kiosk_screen *s) {
	if(s) {
		
		free(s);
		
	}
	return;
}


void p_kiosk_screen_clock(p_kiosk_screen *s) {
	
	/*
	 * Generate all screen bus addresses
	 */
	m_uword command_address = s->screen_start_address;
	m_uword add_char_address = s->screen_start_address + 1;
	m_uword print_char_address = s->screen_start_address + 2;
	m_uword x_loc_address = s->screen_start_address + 3;
	m_uword y_loc_address = s->screen_start_address + 4;
	m_uword color_address = s->screen_start_address + 5;
	m_uword draw_mode_address = s->screen_start_address + 6;
	m_uword draw_1_address = s->screen_start_address + 7;
	m_uword draw_2_address = s->screen_start_address + 8;
	m_uword draw_3_address = s->screen_start_address + 9;
	m_uword draw_4_address = s->screen_start_address + 10;
	m_uword draw_5_address = s->screen_start_address + 11;
	
	// If bus address is command bus
	if (s->screen_bus->address == command_address) {
		
		/* Is write request */
		if (s->screen_bus->rW == M_HIGH) {
			if (s->screen_bus->req && !s->screen_bus->ack)
				{
					int result = 1;
					int temp = 0;
					
					switch (s->screen_bus->data)
						{
							case COMMAND_DRAW_STRING:
								result = p_sdl_render_string(s->sdl_struct, s->string_buffer);
								s->string_buffer[0] = '\0';
								s->string_buffer_location = 0;
								break;
							case COMMAND_DRAW_SHAPE:
								if (s->drawmode == DRAWMODE_PIXEL) {
									result = p_sdl_draw_pixel(s->sdl_struct, s->draw_buffer[0], s->draw_buffer[1]);
								} else if (s->drawmode == DRAWMODE_LINE) {
									result = p_sdl_draw_line(s->sdl_struct, s->draw_buffer[0], s->draw_buffer[1], s->draw_buffer[2], s->draw_buffer[3]);
								} else if (s->drawmode == DRAWMODE_RECT) {
									result = p_sdl_draw_rectangle(s->sdl_struct, s->draw_buffer[0], s->draw_buffer[1], s->draw_buffer[2], s->draw_buffer[3], s->draw_buffer[4]);
								} else if (s->drawmode == DRAWMODE_CIRCLE) {
									result = p_sdl_draw_circle(s->sdl_struct, s->draw_buffer[0], s->draw_buffer[1], s->draw_buffer[2], s->draw_buffer[3]);
								} else {
									result = 1;
								}
								break;
							case COMMAND_DRAW_CLEAR:
								result = p_sdl_clear_screen(s->sdl_struct);
								break;
							case COMMAND_DRAW_RESET:
								
								temp = p_sdl_set_text_cursor_x(s->sdl_struct, 0);
								result = temp | result;
								temp = p_sdl_set_text_cursor_y(s->sdl_struct, 0);
								result = temp | result;
								break;
							case COMMAND_DRAW_CLEAR_RESET: 
								temp = p_sdl_clear_screen(s->sdl_struct);
								result = temp | result;
								temp = p_sdl_set_text_cursor_x(s->sdl_struct, 0);
								result = temp | result;
								temp = p_sdl_set_text_cursor_y(s->sdl_struct, 0);
								result = temp | result;
								break;
							default:
								result = 1;
						}
					
					s->screen_bus->ack = M_HIGH;
					s->last_status = result;
				
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				}
		/* Is read request */		
		}else if (s->screen_bus->rW == M_LOW){
			if (s->screen_bus->req && !s->screen_bus->ack)
				{
				
					s->screen_bus->ack == M_HIGH;
					s->screen_bus->data = s->last_status;
				
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				} 
		}
		
	
			
	
	} else if (s->screen_bus->address == add_char_address) {
		
		/* Is write request */
		if (s->screen_bus->rW == M_HIGH) {
			
			if (s->screen_bus->req && !s->screen_bus->ack)
				{

					if (s->string_buffer_location <= STR_BUFFER_SIZE)
						{
							s->string_buffer[s->string_buffer_location] = s->screen_bus->data;
							s->string_buffer_location += 1;
							s->string_buffer[s->string_buffer_location] = '\0';
							
							s->screen_bus->ack = M_HIGH;
						} 
				
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				} 

		/* Is read request */	
		}else if (s->screen_bus->rW == M_LOW){ 
			if (s->screen_bus->req && !s->screen_bus->ack)
				{
					s->screen_bus->data = s->string_buffer_location;
					s->screen_bus->ack = M_HIGH;
				
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				} 
		}
		
		
	} else if (s->screen_bus->address == print_char_address) {
		
		/* Is write request */
		if (s->screen_bus->rW == M_HIGH) {
			
			if (s->screen_bus->req && !s->screen_bus->ack)
				{
					int result = p_sdl_render_char(s->sdl_struct, s->screen_bus->data);
					s->screen_bus->ack = M_HIGH;
				
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				} 

		/* Is read request */	
		}else if (s->screen_bus->rW == M_LOW){ 
			if (s->screen_bus->req && !s->screen_bus->ack)
				{
					
				
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				} 
		}
		
		
	} else if (s->screen_bus->address == x_loc_address) {

		/* Is write request */
		if (s->screen_bus->rW == M_HIGH) {
			
			if (s->screen_bus->req && !s->screen_bus->ack)
				{

					int result = p_sdl_set_text_cursor_x(s->sdl_struct, s->screen_bus->data); 
					s->screen_bus->ack = M_HIGH;
					
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				} 

		/* Is read request */	
		}else if (s->screen_bus->rW == M_LOW){ 
			if (s->screen_bus->req && !s->screen_bus->ack)
				{
					s->screen_bus->data = p_sdl_get_text_cursor_x(s->sdl_struct);
					s->screen_bus->ack = M_HIGH;
				
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				} 
		}
	} else if (s->screen_bus->address == y_loc_address) {

		/* Is write request */
		if (s->screen_bus->rW == M_HIGH) {
			
			if (s->screen_bus->req && !s->screen_bus->ack)
				{

					int result = p_sdl_set_text_cursor_y(s->sdl_struct, s->screen_bus->data); 
					s->screen_bus->ack = M_HIGH;
					
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				} 

		/* Is read request */	
		}else if (s->screen_bus->rW == M_LOW){ 
			if (s->screen_bus->req && !s->screen_bus->ack)
				{
					s->screen_bus->data = p_sdl_get_text_cursor_y(s->sdl_struct);
					s->screen_bus->ack = M_HIGH;
				
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				} 
		}
	} else if (s->screen_bus->address == color_address) {

		/* Is write request */
		if (s->screen_bus->rW == M_HIGH) {
			
			if (s->screen_bus->req && !s->screen_bus->ack)
				{

					int result = p_sdl_set_color(s->sdl_struct, s->screen_bus->data); 
					s->screen_bus->ack = M_HIGH;
					
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				} 

		/* Is read request */	
		}else if (s->screen_bus->rW == M_LOW){ 
			if (s->screen_bus->req && !s->screen_bus->ack)
				{
					s->screen_bus->data = p_sdl_get_color(s->sdl_struct);
					s->screen_bus->ack = M_HIGH;
				
				// Then, we are not a request
				}else if (s->screen_bus->ack == M_HIGH){
					// Ensure ACK is low (is unset)
					s->screen_bus->ack = M_LOW;
				} 
		}
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
