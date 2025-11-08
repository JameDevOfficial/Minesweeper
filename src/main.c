#include "libs/game.h"
#include "libs/lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int mode = handleMenu();
    Grid grid = generateGridRandom(mode);
    getch();
    int result = handleGame(grid);
    if (result == 1){
        printf("You won!");
        getch();
    }
    else {
        printf("Exited with code %d", result);
    }
    
    freeGrid(&grid); 
    return EXIT_SUCCESS;
} 