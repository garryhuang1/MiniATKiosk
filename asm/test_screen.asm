.constant	CMD		0x4000
.constant	ADDBUF	0x4001

.constant	CHAR	65

.address 0x2000
 
!main
	MOVI r45, 25
	MOVI r46, CHAR
	MOVI r44, 0
!loop
	STOR r46, [ADDBUF]
	ADD r44, r44, (1)
	ADD r46, r46, (1)
	BRALE r44, r45 [!loop]

!done
	MOVI r46, 0
	STOR r46, [CMD]

!inf
	BRA	[!inf]
