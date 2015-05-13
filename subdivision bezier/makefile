all: subdivision

subdivision: subdivision.o
	gcc subdivision.o -o subdivision -lglut -lGL -lGLU -lm

subdivision.o: subdivision.cpp
	gcc -c subdivision.cpp

clean: 
	rm -rf *.o subdivision
