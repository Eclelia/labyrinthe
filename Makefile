CFLAGS = -Wall -Wextra -std=c99 -pedantic
CPPFLAGS = -I ./include/
BIN_F = ./bin

all: labyrinth test_labyrinth

labyrinth: $(BIN_F)/main.o $(BIN_F)/labyrinth_creation.o
	gcc $^ -o $@ -lm

test_labyrinth: $(BIN_F)/test_labyrinth.o
	gcc $^ -o $@ -lm

$(BIN_F)/test_labyrinth.o: src/test/test_labyrinth.c
	gcc $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(BIN_F)/%.o: src/%.c
	gcc $(CFLAGS) $(CPPFLAGS) $< -c -o $@

clean :
	rm $(BIN_F)/*.o