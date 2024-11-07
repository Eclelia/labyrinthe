CFLAGS = -Wall -Wextra -std=c99 -pedantic
CPPFLAGS = -I ./include/
BIN_F = ./obj

all: labyrinth test_labyrinth

labyrinth: $(BIN_F)/main.o $(BIN_F)/labyrinth_creation.o $(BIN_F)/display.o $(BIN_F)/labyrinth.o $(BIN_F)/game.o
#sudo apt-get install libncurses5-dev libncursesw5-dev
	gcc $^ -o $@ -lm -lncurses -lc

test_labyrinth: $(BIN_F)/test_labyrinth.o
	gcc $^ -o $@ -lm

$(BIN_F)/test_labyrinth.o: src/test/test_labyrinth.c
	gcc $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(BIN_F)/main.o: src/main.c
	gcc $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(BIN_F)/%.o: src/%.c include/%.h
	gcc $(CFLAGS) $(CPPFLAGS) $< -c -o $@

clean :
	rm $(BIN_F)/*.o