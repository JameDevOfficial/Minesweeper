#include "libs/game.h"
#include "libs/lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main()
{
    int mode = handleMenu();
    Grid grid = generateGridRandom(mode);
    int result = handleGame(mode, grid);
}

Grid generateGridRandom(mode){
    uint32_t width, height, totalBombs;
    
    if (mode == 1) { // Easy
        width = 9; height = 9; totalBombs = 10;
    } else if (mode == 2) { // Medium
        width = 16; height = 16; totalBombs = 40;
    } else { // Hard
        width = 30; height = 16; totalBombs = 99;
    }
    
    Grid *grid = malloc(sizeof(Grid) + totalBombs * sizeof(Mine));
    grid->width = width;
    grid->height = height;
    grid->totalBombs = totalBombs;
    
    return *grid;
}