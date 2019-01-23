COMPONENTS = game.o saves.o ai.o
LIBS = -ljson-c

all: a.out clean


a.out: main.c $(COMPONENTS)
	gcc -std=c99 main.c $(COMPONENTS) $(LIBS) -Wall

game.o : game.c
	gcc -c -std=c99 game.c

saves.o : saves.c
	gcc -c -std=c99 saves.c -ljson-c

ai .o : ai.c
	gcc -c -std=c99 ai .c


clean:
	rm *.o
