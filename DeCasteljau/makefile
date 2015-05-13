all: deCasteljau

deCasteljau: deCasteljau.o
	gcc deCasteljau.o -o deCasteljau -lglut -lGL -lGLU -lm

deCasteljau.o: deCasteljau.cpp
	gcc -c deCasteljau.cpp

clean: 
	rm -rf *.o deCasteljau
