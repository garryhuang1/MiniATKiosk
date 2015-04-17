.constant	CMDB	0x4012
.constant	BUFF	0x4013
.constant	PRTC	0x4014
.constant	COLB	0x4017

.constant	CHAR	60

.address 0x2000

# This version uses the character buffer to push each
# character from the string into the character buffer
# and then displays the character buffer

BRA [!main]

!string1
	"Hello World Bitches"	

 
!main
	
	MOVR r1, r0
	MOVI r3, 7
	STOR r3, [COLB]
	
	
!loop

	LOAD r2, [r1 + !string1]
	BRAE {F}	r2, r0 [!done]
	STOR r2, [BUFF]
	ADD r1, r1, (1)
	BRA [!loop]

!done

	STOR r0, [CMDB]
	

!inf
	BRA	[!inf]


