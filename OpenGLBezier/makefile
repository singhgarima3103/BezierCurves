all: OpenGLBezier

OpenGLBezier: OpenGLBezier.o
	gcc OpenGLBezier.o -o OpenGLBezier -lglut -lGL -lGLU -lm

OpenGLBezier.o: OpenGLBezier.cpp
	gcc -c OpenGLBezier.cpp

clean: 
	rm -rf *.o OpenGLBezier
