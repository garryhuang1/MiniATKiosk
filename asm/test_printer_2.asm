.constant	CMD		0x4040
.constant	ADDCHAR	0x4042

.constant	CHAR	65

.address 0x2000
 
!main
	MOVI r44, 0
	MOVI r45, 10
	MOVI r46, CHAR
	
!loop
	STOR r46, [ADDCHAR]
	ADD r46, r46, (1)
	ADD r44, r44, (1)
	BRALE r44, r45 [!loop]

!done
	

!inf
	BRA	[!inf]
