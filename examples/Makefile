CC = cc
CFLAGS = -I "../src"
LFLAGS = -L .. -lbeep -lm

all: hello_beep.bin sus.bin

hello_beep.bin: hello_beep.c
	$(CC) $< $(CFLAGS) $(LFLAGS) -o hello_beep.bin

sus.bin: sus.c
	$(CC) $< $(CFLAGS) $(LFLAGS) -o sus.bin

clean:
	rm *.bin
