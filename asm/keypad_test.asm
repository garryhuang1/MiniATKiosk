.constant KEYPAD_CMD	0x4030
.constant KEYPAD_SCR	0x4031

.constant	DATA		2

.address 0x2000

!main
	MOVI r10, 0

!loop
	LOAD r20, [KEYPAD_CMD]
	BRALE r10, r20 [!loop]


