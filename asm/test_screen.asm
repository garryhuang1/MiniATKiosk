.constant	CMD		0x4012
.constant	ADDBUF	0x4013
.constant	COLOR	0x4017

.constant	CHAR	65

.address 0x2000
 
!main
	MOVI r45, 35
	MOVI r46, CHAR
	MOVI r44, 0
	MOVI r20, 1
	STOR r20, [COLOR]
!loop
	STOR r46, [ADDBUF]
	ADD r44, r44, (1)
	ADD r46, r46, (1)
	BRALE r44, r45 [!loop]

!done
	MOVI r46, 0
	STOR r46, [CMD]

	MOVI r46, 1
	STOR r46, [CMD]

!inf
	BRA	[!inf]
