LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

all: a.out

a.out: display.c
	gcc -std=c99 display.c $(LIBS)

clean:
	rm *.os
