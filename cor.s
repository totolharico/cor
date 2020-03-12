;
#
.comment       "coucou" #
;
#
.name    "This city needs m"
;
#
loop:
yo: #
	sti r1, %:live, %1  
live:
        live %0
        ld %:loop, r2
        zjmp %:loop
