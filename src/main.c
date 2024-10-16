#include <stdlib.h>
#include "labyrinth.h"
#include "display.h"
#include "labyrinth_creation.h"

int main(int argc, char const *argv[])
{
    Labyrinth* lab = init_labyrinth(9, 7);
    init_unformed_labyrinth(lab);

    display_game(*lab);

    free(lab);
    return 0;
}
