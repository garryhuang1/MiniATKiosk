.constant	KEYP	0x4000
.constant	CMDB	0x4012
.constant	PRCH	0x4014

.constant	CHAR	60

.address 0x2000




!main
	MOVI r21, 68
!loop
	LOAD r20, [KEYP]
	BRAE r20, r21 [!clear]
	BRANE r20, r0, [!print]
	BRA [!loop]
!print
	STOR r20, [PRCH]
	BRA [!loop]
!clear
	MOVI r15, 4
	STOR r15, [CMDB]
	BRA [!loop]

