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
} Pos;

typedef struct
{
    Pos pos;
    bool uncovered;
    bool flagged;
    bool isMine;
    uint32_t value;
} Tile;

typedef struct
{
    uint32_t width;
    uint32_t height;
    uint32_t totalMines;
    Tile **tiles;
    Pos current;
} Grid;

#define LINE_LENGTH 66
int handleGame(int difficulty, Grid grid);

int handleMenu()
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
    return currentOption;
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

    grid.tiles = malloc(height * sizeof(Tile *));
    for (uint32_t y = 0; y < height; y++)
    {
        grid.tiles[y] = malloc(width * sizeof(Tile));
    }
    for (uint32_t y = 0; y < height; y++)
    {
        for (uint32_t x = 0; x < width; x++)
        {
            grid.tiles[y][x].pos.x = x;
            grid.tiles[y][x].pos.y = y;
            grid.tiles[y][x].uncovered = false;
            grid.tiles[y][x].flagged = false;
            grid.tiles[y][x].isMine = false;
        }
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
        uint32_t x = positions[i] % width;
        uint32_t y = positions[i] / width;
        grid.tiles[y][x].isMine = true;
        printf("Set Tile X: %u, Y: %u to mine\n", x, y);
    }
    free(positions);

    return grid;
}

void freeGrid(Grid *grid)
{
    if (grid->tiles)
    {
        for (uint32_t y = 0; y < grid->height; y++)
        {
            free(grid->tiles[y]);
        }
        free(grid->tiles);
        grid->tiles = NULL;
    }
}

void renderGrid(Grid *grid)
{
    if (!grid->tiles)
        return;
    for (uint32_t y = 0; y < grid->height; y++)
    {
        for (uint32_t x = 0; x < grid->width; x++)
        {
            addTextToCache(" ");
            if (grid->tiles[y][x].flagged == true)
            {
                char buffer[50];
                int fg_index = color_to_ansi256((Color){255, 100, 100});
                int bg_index = color_to_ansi256_bg((Color){255, 100, 100});
                sprintf(buffer, "\x1b[38;5;%dm\x1b[48;5;%dm \x1b[0m", fg_index, bg_index);
                addTextToCache(buffer);
            }
            else if (grid->tiles[y][x].pos.x == grid->current.x && grid->tiles[y][x].pos.y == grid->current.y)
            {
                char buffer[50];
                int fg_index = color_to_ansi256((Color){100, 255, 100});
                int bg_index = color_to_ansi256_bg((Color){100, 255, 100});
                sprintf(buffer, "\x1b[38;5;%dm\x1b[48;5;%dm \x1b[0m", fg_index, bg_index);
                addTextToCache(buffer);
            }
            else if (grid->tiles[y][x].uncovered == true)
            {
                char buffer[10];
                sprintf(buffer, "%d", grid->tiles[y][x].value);
                addTextToCache(buffer);
            }
            else if (grid->tiles[y][x].isMine == true)
            {
                addTextToCache("X");
            }
            else
            {
                char buffer[50];
                int fg_index = color_to_ansi256((Color){100, 100, 100});
                int bg_index = color_to_ansi256_bg((Color){100, 100, 100});
                sprintf(buffer, "\x1b[38;5;%dm\x1b[48;5;%dm \x1b[0m", fg_index, bg_index);
                addTextToCache(buffer);
            }
            addTextToCache(" ");
        }
        addTextToCache("\n\n");
    }
    printCache();
}

int handleGame(int difficulty, Grid grid)
{
    bool running = true;


    while (running == true) {
        cls();
        renderGrid(&grid);
        char inp = getch();
        switch (inp)
        {
        case 'W':
        case 'w': // Up
            if (grid.current.y > 0) grid.current.y -= 1;
            break;
        case 'S':
        case 's': // Down
            grid.current.y += 1;
            if (grid.current.y > grid.height - 1)
                grid.current.y = grid.height - 1;
            break;
        case 'A':
        case 'a': // Left
            if (grid.current.x > 0) grid.current.x -= 1;
            break;
        case 'd': // Right
            grid.current.x += 1;
            if (grid.current.x > grid.width - 1)
                grid.current.x = grid.width - 1;
            break;
        case 13:
            grid.tiles[grid.current.y][grid.current.x].uncovered = true;

            if (grid.tiles[grid.current.y][grid.current.x].isMine == true)
            {
                return -1;
            }
        case 8:
            grid.tiles[grid.current.y][grid.current.x].flagged = true;
        default:
            break;
        }
    }
    return 1;
}
#endif