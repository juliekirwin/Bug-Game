.PHONY: all clean
.DEFAULT_GOAL: all
ZIMMER_OBJECTS = dice.o gamefiles.o wpn.o player.o human.o bug.o phc.o board.o cell.o
MY_OBJECTS = 
EXECUTABLES = p3test
OBJECTS = $(MY_OBJECTS) $(ZIMMER_OBJECTS)
all: $(EXECUTABLES)

p3test: p5.cpp $(OBJECTS)
	g++ -Wall -Wextra -g -o p3test p5.cpp $(OBJECTS)

$(MY_OBJECTS):
	g++ -Wall -Wextra -c -g $(*F).cpp

clean:
	rm -rf  $(MY_OBJECTS) $(EXECUTABLES) *~