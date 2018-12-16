COMPONENTS = saves.o
LIBS = -ljson-c

all: a.out clean


a.out: main.c $(COMPONENTS)
	gcc -std=c99 main.c $(COMPONENTS) $(LIBS) -Wall

saves.o : saves.c
	gcc -c -std=c99 saves.c -ljson-c


clean:
	rm *.o
