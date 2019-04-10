# NOTE: All indented lines are indented with a tab character.

.PHONY: clean
CFLAGS= -ansi -pedantic -O0 -Wall
DFLAGS = -g

all: frupal

frupal: frupal_main.cpp
	g++ -g -o frupal_main $(CFLAGS) $(DFLAGS) frupal_main.cpp
	
clean:
	rm -f *.o frupal_main

