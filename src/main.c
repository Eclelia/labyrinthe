#include <stdlib.h>
#include <stdio.h>
#include "labyrinth.h"
#include "display.h"
#include "labyrinth_creation.h"

int main(int argc, char const *argv[])
{
    Labyrinth* lab = init_labyrinth(1001, 1001);
    init_unformed_labyrinth(lab);
    create_labyrinth_path(lab);
    printf("\n\n");

    display_game(*lab);

    destroy_labyrinth(lab);
    return 0;
}
