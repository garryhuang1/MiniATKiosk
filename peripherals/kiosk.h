#ifndef _KIOSK_H_
#define _KIOSK_H_

#include "miniat/miniat.h"
#include "p_kiosk_sdl.h"

typedef struct kiosk kiosk;

extern kiosk * p_kiosk_new(m_uword R_address, m_uword W_address);

//extern void p_kiosk_bus_connector_set(kiosk *k, m_bus *bus);

extern void p_kiosk_free(kiosk *k);

extern void p_kiosk_read_clock(kiosk *k, SDL_Event *e);

extern void p_kiosk_write_clock(kiosk *k);

extern m_bus p_kiosk_get_read_bus(kiosk *k);
extern m_bus p_kiosk_get_write_bus(kiosk *k);

extern void p_kiosk_set_read_bus(kiosk *k, m_bus bus);
extern void p_kiosk_set_write_bus(kiosk *k, m_bus bus);

#endif /*KIOSK_H_ */