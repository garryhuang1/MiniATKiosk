.constant	CMD			0x4000
.constant	DRAWMODE	0x4006
.constant	DRAW1		0x4007
.constant	DRAW2		0x4008
.constant	DRAW3		0x4009
.constant	DRAW4		0x400A
.constant	DRAW5		0x400B

.constant	CHAR	65

.address 0x2000
 
!main
	MOVI r10, 2
	STOR r10, [DRAWMODE]
	MOVI r20, 0
	MOVI r21, 400
	MOVI r10, 50
	STOR r10, [DRAW2]
	MOVI r10, 100
	STOR r10, [DRAW3]
	MOVI r10, 100
	STOR r10, [DRAW4]
!loop
	NOP
	NOP
	MOVI r10, 2
	STOR r10, [CMD]
	NOP
	NOP
	STOR r20, [DRAW1]
	MOVI r10, 1
	STOR r10, [DRAW5]
	MOVI r10, 1
	STOR r10, [CMD]
	ADD r20, r20, (1)
	NOP
	NOP
	NOP
	NOP
	BRALE r20, r21 [!loop]

	MOVI r20, 0
	BRA [!loop]
	
	

