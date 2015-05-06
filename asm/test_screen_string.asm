# @author Matt Preisendorfer

.constant	CMDB	0x4012
.constant	RECW	0x4041
.constant	RECP	0x4042
.constant	COLB	0x4017

.address 			0x2000

BRA [!main]

!string1
	"RIP in peace"	

 
!main
	
	MOVR r1, r0
	MOVI r3, 1
	STOR r3, [COLB]
	
	
!loop

	LOAD r2, [r1 + !string1]
	BRAE {F}	r2, r0 [!done]
	STOR r2, [RECW]
	STOR r3, [RECP]
	ADD r1, r1, (1)
	BRA [!loop]

!done
	

!inf
	BRA	[!inf]


