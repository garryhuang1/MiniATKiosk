.constant	CMDB	0x4040
.constant	CHRB	0x4042

.constant	CHAR	60

.address 0x2000

BRA [!main]

!string1
	"Hello World"	

!main
	
	MOVR r1, r0
	MOVI r3, 2
		
!loop

	LOAD r2, [r1 + !string1]
	BRAE {F}	r2, r0 [!done]
	STOR r2, [CHRB]
	ADD r1, r1, (1)
	BRA [!loop]

!done
	

!inf
	BRA	[!inf]

