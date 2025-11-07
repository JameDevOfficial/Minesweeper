#ifndef GAME_H
#define GAME_H

#include "lib.h"
#include "stdbool.h"
#include <conio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint32_t x;
    uint32_t y;
} Mine;

typedef struct
{
    uint32_t width;
    uint32_t height;
    uint32_t totalMines;
    Mine mines[];
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

    Grid *grid = malloc(sizeof(Grid) + totalMines * sizeof(Mine));
    grid->width = width;
    grid->height = height;
    grid->totalMines = totalMines;

    uint32_t totalPositions = width * height;
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

    for (uint32_t i = 0; i < totalMines; i++)
    {
        grid->mines[i].x = positions[i] % width;
        grid->mines[i].y = positions[i] / width;
        printf("%d: X: %d Y: %d\n", i, grid->mines[i].x, grid->mines[i].y);
    }

    free(positions);

    return *grid;
}

int handleGame(int difficulty, Grid grid)
{
    cls();

    return 1;
}
#endif