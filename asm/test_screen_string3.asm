.constant	CMDB	0x4012
.constant	PRTC	0x4014
.constant	COLB	0x4017
.constant	XLOC	0x4015
.constant	YLOC	0x4016

.constant	CHAR	60

.address 0x2000


<<<
	r1: counter
	r2: string1 holder
	r3: text color
	r4: string2
	r5: xloc
	r6: yloc
>>>
	

BRA [!main]

!string1
	"Hello Bitches"

!string2
	"Welcome to Kiosk!"

 
!main

	MOVR r1, r0
	MOVI r3, 7
	STOR r3, [COLB]
	
	
!string1_print

	LOAD r2, [r1 + !string1]
	BRAE {F}	r2, r0 [!done1]
	STOR r2, [PRTC]
	ADD r1, r1, (1)
	BRA [!string1_print]

!done1
	
	MOVR r1, r0
	MOVI r3, 2
	STOR r3, [COLB]
	
	MOVI r5, 40
	MOVI r6, 70
	STOR r5, [XLOC]
	STOR r6, [YLOC]
	
	

!string2_print

	LOAD r4, [r1 + !string2]
	BRAE {F}	r4, r0 [!done2]
	STOR r4, [PRTC]
	ADD r1, r1, (1)
	BRA [!string2_print]

!done2

!inf
	BRA	[!inf]


