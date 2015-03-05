#ifndef _KIOSK_KEYPAD_H_
#define _KIOSK_KEYPAD_H_

#include "miniat/miniat.h"

typedef struct p_kiosk_keypad p_kiosk_keypad;

extern p_kiosk_keypad * p_kiosk_keypad_new(m_uword keypad_command_address,
											m_uword keypad_data_address);

extern void p_kiosk_keypad_free(p_kiosk_keypad *k);

extern void p_kiosk_keypad_clock(p_kiosk_keypad *k);

extern m_bus p_kiosk_keypad_get_bus(p_kiosk_keypad *k);

extern void p_kiosk_keypad_set_bus(p_kiosk_keypad *k, m_bus bus);

#endif /* _KIOSK_KEYPAD_H_ */