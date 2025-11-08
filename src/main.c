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
    int result = handleGame(mode, grid);
    freeGrid(&grid);
    return EXIT_SUCCESS;
}