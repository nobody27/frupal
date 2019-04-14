# NOTE: All indented lines are indented with a tab character.

.PHONY: clean
CFLAGS= -pedantic -O0 -Wall
DFLAGS= -g
HEADER_FILES= boardNtile.h
SOURCE_FILES= frupal_main.cpp boardNtile.cpp 


all: frupal  

frupal: $(HEADER_FILES) $(SOURCE_FILES)
	echo "source files: $(SOURCE_FILES)"
	echo "header files: $(HEADER_FILES)"
	g++ -g -o frupal_main $(CFLAGS) $(DFLAGS) $(SOURCE_FILES)
	
clean:
	rm -f *.o frupal_main

