.constant	CMD			0x4012
.constant	DRAWMODE	0x4018
.constant	DRAW1		0x4019
.constant	DRAW2		0x401A
.constant	DRAW3		0x401B
.constant	DRAW4		0x401C
.constant	DRAW5		0x401D

.constant	CHAR	65

.address 0x2000
 
!main
	MOVI r10, 1
	STOR r10, [DRAWMODE]
	MOVI r10, 50
	STOR r10, [DRAW1]
	MOVI r10, 50
	STOR r10, [DRAW2]
	MOVI r10, 100
	STOR r10, [DRAW3]
	MOVI r10, 100
	STOR r10, [DRAW4]
	MOVI r10, 1
	STOR r10, [DRAW5]
	MOVI r10, 1
	STOR r10, [CMD]
	

	

