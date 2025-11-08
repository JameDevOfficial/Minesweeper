#ifndef GAME_H
#define GAME_H

#include "lib.h"
#include "stdbool.h"
#include <conio.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct {
    uint32_t x;
    uint32_t y;
} Pos;

typedef struct 
{
    Pos pos;
    bool uncovered;
    bool flagged;
    bool isMine;
} Tile;

typedef struct
{
    uint32_t width;
    uint32_t height;
    uint32_t totalMines;
    Tile *tiles;
    Pos current;
} Grid;

#define LINE_LENGTH 66
int handleGame(int difficulty, Grid grid);

bool handleMenu()
{
    printf_c_s("////////////////////////////////////////////////////////////////// \n"
               "//  __  __ _                                                    // \n"
               "// |  \\/  (_)_ __   ___  _____      _____  ___ _ __   ___ _ __  // \n"
               "// | |\\/| | | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__| // \n"
               "// | |  | | | | | |  __/\\__  \\ V  V /  __/  __/ |_) |  __/ |    // \n"
               "// |_|  |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|    // \n"
               "//                                            |_|               // \n"
               "////////////////////////////////////////////////////////////////// \n",
               (Color){255, 0, 0},
               BOLD);
    print_line(LINE_LENGTH);
    printf("\nDifficulty:\n");
    printf("   1. Easy\n");
    printf("   2. Medium\n");
    printf("   3. Hard\n");

    int inp = 0;
    int currentOption = 1; // 1 - 3
    while (!(inp == 13 || inp == 'q' || inp == 'Q'))
    {
        inp = getch();
        switch (inp)
        {
        case 'W':
        case 'w': // Up
            currentOption -= 1;
            break;
        case 'S':
        case 's': // Down
            currentOption += 1;
            break;
        case 'A':
        case 'a': // Left
            break;
        case 'D':
        case 'd': // Right
            break;
        case 13:
            return currentOption;
        default:
            break;
        }

        if (currentOption < 1)
            currentOption = 1;
        else if (currentOption > 3)
            currentOption = 3;
        printf("\x1b[3A");

        if (currentOption == 1)
            printf_c_ms("   1. Easy     \n", (Color){255, 255, 255}, (TextStyle[]){INVERTED}, 1);
        else
            printf("   1. Easy     \n");

        if (currentOption == 2)
            printf_c_ms("   2. Medium   \n", (Color){255, 255, 255}, (TextStyle[]){INVERTED}, 1);
        else
            printf("   2. Medium   \n");

        if (currentOption == 3)
            printf_c_ms("   3. Hard     \n", (Color){255, 255, 255}, (TextStyle[]){INVERTED}, 1);
        else
            printf("   3. Hard     \n");
    }
    return true;
}

Grid generateGridRandom(int mode)
{
    uint32_t width, height, totalMines;

    if (mode == 1)
    { // Easy
        width = 9;
        height = 9;
        totalMines = 10;
    }
    else if (mode == 2)
    { // Medium
        width = 16;
        height = 16;
        totalMines = 40;
    }
    else
    { // Hard
        width = 30;
        height = 16;
        totalMines = 99;
    }

    Grid grid;
    grid.width = width;
    grid.height = height;
    grid.totalMines = totalMines;
    grid.current = (Pos){width / 2, height / 2};

    uint32_t totalPositions = width * height;
    grid.tiles = malloc(totalPositions * sizeof(Tile));

    // Initialize all tiles
    for (uint32_t i = 0; i < totalPositions; i++)
    {
        grid.tiles[i].pos.x = i % width;
        grid.tiles[i].pos.y = i / width;
        grid.tiles[i].uncovered = false;
        grid.tiles[i].flagged = false;
        grid.tiles[i].isMine = false;
    }

    uint32_t *positions = malloc(totalPositions * sizeof(uint32_t));
    for (uint32_t i = 0; i < totalPositions; i++)
    {
        positions[i] = i;
    }

    // Fisher-Yates shuffle
    for (uint32_t i = 0; i < totalMines; i++)
    {
        uint32_t j = i + rand() % (totalPositions - i);
        uint32_t temp = positions[i];
        positions[i] = positions[j];
        positions[j] = temp;
    }

    // Set mines
    for (uint32_t i = 0; i < totalMines; i++)
    {
        grid.tiles[positions[i]].isMine = true;
        //printf("Set Tile X: %d, Y: %d to mine\n", grid.tiles[positions[i]].pos.x, grid.tiles[positions[i]].pos.y);
    }

    free(positions);

    return grid;
}

void renderGrid(Grid *grid){
    for (int h = 0; h< grid->height; h++){
        for (int w = 0; w< grid->width; w++){
            ; 
        }
    }
}

int handleGame(int difficulty, Grid grid)
{    cls();

    return 1;
}
#endif