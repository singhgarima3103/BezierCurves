all: bezier

bezier: bezier.o
	gcc bezier.o -o bezier -lglut -lGL -lGLU -lm

bezier.o: bezier.c
	gcc -c bezier.c

clean: 
	rm -rf *.o bezier
