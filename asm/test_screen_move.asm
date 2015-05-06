.constant	CMD		0x4012
.constant	ADDCHAR	0x4014
.constant	MOVEX	0x4015
.constant	MOVEY	0x4016

.constant	CHAR	65

.address 0x2000
 
!main
	MOVI r44, 0
	MOVI r45, 5
	MOVI r46, CHAR
	
!move
	MOVI r20, 40
	MOVI r21, 70
	STOR r20, [MOVEX]
	STOR r20, [MOVEY]
	
!loop
	STOR r46, [ADDCHAR]
	ADD r46, r46, (1)
	ADD r44, r44, (1)
	BRALE r44, r45 [!loop]

!done
	

!inf 
	BRA	[!inf]
