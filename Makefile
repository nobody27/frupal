# NOTE: All indented lines are indented with a tab character.

.PHONY: clean
CFLAGS= -pedantic -O0 -Wall -std=c++14
DFLAGS= -g
HEADER_FILES= boardNtile.h GameManager.h MainMenu.h GameMenu.h OptionsMenu.h seeker.h resources.h
SOURCE_FILES= frupal_main.cpp boardNtile.cpp GameManager.cpp MainMenu.cpp GameMenu.cpp OptionsMenu.cpp seeker.cpp resources.cpp


all: frupal  

frupal: $(HEADER_FILES) $(SOURCE_FILES)
	echo "source files: $(SOURCE_FILES)"
	echo "header files: $(HEADER_FILES)"
	g++ -g -o frupal_main $(CFLAGS) $(DFLAGS) $(SOURCE_FILES)
	
clean:
	rm -f *.o frupal_main

itso: frupal
	./frupal_main
