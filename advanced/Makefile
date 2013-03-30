CC = g++
CFLAGS = -Wall
PROG = game

SRCS = game.cpp imageloader.cpp
LIBS = -lglut -lGL -lGLU -lalut -lopenal

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -w -o $(PROG) $(SRCS) $(LIBS) 

clean:
	rm -f $(PROG)
