.constant	TERM	0x4010
.constant	KEYB	0x4011

.address 0x2000

!main
    MOVI r40, !string
    NOP

!prompt
    LOAD r20, [r40]
    BRAE {F} r20, r0, [!done]

    STOR r20, [TERM]
    ADD	r40, r40, (1)
    BRA	[!prompt]
!done
    MOVI r41, CR
    MOVI r42, LF
    STOR r41, [TERM]
    STOR r42, [TERM]

!echo_loop
    LOAD r1, [KEYB] # Read from the KB
    STOR r1, [TERM] # Write to the terminal
    BRA [!echo_loop]

!string
    "MiniAT Echo Terminal, type a string hit enter and the MiniAT echo's it back!"

