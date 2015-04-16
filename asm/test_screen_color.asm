.constant	CMD		0x4012
.constant	ADDBUF	0x4013
.constant	COLOR	0x4017

.constant	CHAR	65

.address 0x2000
 
!main
	MOVI r10, 4
	MOVI r21, 6
	MOVI r20, 1
!color

	STOR r20, [COLOR]
	

	MOVI r45, 31
	MOVI r46, CHAR
	MOVI r44, 0
	
!loop
	STOR r46, [ADDBUF]
	ADD r44, r44, (1)
	ADD r46, r46, (1)
	
	BRALE r44, r45 [!loop]

	MOVI r46, 0
	STOR r46, [CMD]

	ADD r20, r20, (1)
	
	MOVI r11, 2000
	MOVI r12, 0
!wait
	NOP
	NOP
	NOP
	NOP
	ADD r12, r12, (1)
	BRALE r12, r11 [!wait]
	
	BRALE r20, r21, [!color]
	

	MOVI r20, 0
	
	BRA [!color]
	
!done
	

