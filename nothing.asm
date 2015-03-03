.constant	TERM	0x4020

.address 0x2000

!main
	MOVI r41, 48
!nothing
	STOR r41, [TERM]
	BRA [!nothing]
