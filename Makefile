.POSIX:

CC = cc
OBJ = beep.o
# No -std=XX due to nanosleep() being POSIX-specific
CFLAGS = -pedantic-errors -Wall -Wextra -O2

all: libbeep.a

libbeep.a: $(OBJ)
	ar rcs libbeep.a *.o

beep.o: src/beep.c
	$(CC) -c $< $(CFLAGS)

src/beep.c: src/beep.h

clean:
	rm *.o libbeep.a
