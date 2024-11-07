#include <stdlib.h>
#include <stdio.h>
#include "labyrinth.h"
#include "display.h"
#include "labyrinth_creation.h"
#include "game.h"

int main()
{
    Labyrinth* lab = init_labyrinth(15, 13);
    init_unformed_labyrinth(lab);

    init_create_recursive_labyrinth_path(lab);

    display_game_square(*lab); 
    
    destroy_labyrinth(lab);

    handle_game();
}
