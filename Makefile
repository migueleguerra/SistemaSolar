# makefile template
#
# Compiler
CC=g++

#gcc -v -framework GLUT -framework OpenGL BasicOpenGL.cpp -o code2 -Wdeprecated-declarations

# Compile Flags
CFLAGS= -v -g -c
LDFLAGS=
ifeq ($(USER_ENV),linux)
LIBS=-lglut -lGLU -lGL -lm
else
LIBS=-framework GLUT -framework OpenGL
endif
DEBUG=-ggdb

all: main

main: main.cpp Planeta.cpp
	$(CC) $(DEBUG) $(LIBS) stb_image.c main.cpp Planeta.cpp Universo.cpp texture.cpp  -o solarSis



#ex5: pract02-5.o
#	$(CC) $(DEBUG) pract02-5.o -o ex05

#pract02-5.o: pract02-5.c
#	$(CC) $(CFLAGS) pract02-5.c	

clean:
	rm solarSis