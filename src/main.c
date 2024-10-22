#include <stdlib.h>
#include <stdio.h>
#include "labyrinth.h"
#include "display.h"
#include "labyrinth_creation.h"

int main()
{
    Labyrinth* lab = init_labyrinth(1025, 1025);
    init_unformed_labyrinth(lab);

    init_create_recursive_labyrinth_path(lab);

    //display_game_square(*lab); 
    
    destroy_labyrinth(lab);

    //ask_menu_option();

    

    /*char menu_choice = '\0';
    do{
        display_menu();
        scanf("%c", &menu_choice);
        while (getchar() != '\n');

        if(menu_choice == 'C' || menu_choice == 'c'){
            //créer un labyrith (avec ou sans affichage)
        }
        else if(menu_choice == 'L' || menu_choice == 'l'){
            //Charger lab enregistré
        }
        else if(menu_choice == 'P' || menu_choice == 'p'){
            //Jouer
        }        
    }while (menu_choice != 'q' && menu_choice != 'Q');*/
    return 0;
}
