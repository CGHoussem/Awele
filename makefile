COMPONENTS = game.o saves.o ai.o display.o ingame.o
LIBS = -ljson-c -lSDL2 -lSDL2_image -lSDL2_ttf

all: a.out clean


a.out: main.c $(COMPONENTS)
	gcc -std=c99 main.c $(COMPONENTS) $(LIBS) -Wall

game.o : game.c
	gcc -c -std=c99 game.c

saves.o : saves.c
	gcc -c -std=c99 saves.c -ljson-c

ai .o : ai.c
	gcc -c -std=c99 ai .c

display.o: SDL/display.c
	gcc -c -std=c99 SDL/display.c -ljson-c -lSDL2 -lSDL2_image -lSDL2_ttf

ingame.o: SDL/ingame.c
	gcc -c -std=c99 SDL/ingame.c -ljson-c -lSDL2 -lSDL2_image -lSDL2_ttf


clean:
	rm *.o
