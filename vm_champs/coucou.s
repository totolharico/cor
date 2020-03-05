.name       "Batman"
.comment    "This city needs me"


coucou:
loop:
		live %5
live:
        live %0
        ld %0, r2
  zjmp %:coucou
