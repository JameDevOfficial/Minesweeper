#ifndef GAME_H
#define GAME_H

#include "lib.h"
#include "stdbool.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#ifdef WIN32
#include <conio.h>
#endif

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
    bool minesPlaced;
    uint32_t coveredTilesLeft;
} Grid;

#define LINE_LENGTH 66
int handleGame(Grid grid);
void printMenuHeader(char highscores[3][10]);

void printOptions(int currentOption)
{
    print_style("Difficulty:\n", BOLD);
    if (currentOption == 1)
        print_c_ms("   1. Easy     \n", (Color){255, 255, 255}, (TextStyle[]){INVERTED}, 1);
    else
        printf("   1. Easy     \n");

    if (currentOption == 2)
        print_c_ms("   2. Medium   \n", (Color){255, 255, 255}, (TextStyle[]){INVERTED}, 1);
    else
        printf("   2. Medium   \n");

    if (currentOption == 3)
        print_c_ms("   3. Hard     \n", (Color){255, 255, 255}, (TextStyle[]){INVERTED}, 1);
    else
        printf("   3. Hard     \n");
}

void printHelp(char highscores[3][10], int currentOption)
{
    cls();
    print_style("\nTips:\n", BOLD);
    printf("   - Use WASD to move around (menu + game) and enter to select (menu)\n   - Press q to exit\n");
    print_style("\nGame Controls:", BOLD);
    printf("\n   - WASD: move around\n   - Enter: Reveal a tile\n   - Backspace: Mark/Unmark tile as flagged\n   The game ends as soon as all tiles that are NOT a mine are uncovered.\n");
    print_line(LINE_LENGTH);

    print_style("\nPress any key to return . . .", ITALIC);
    getch();
    cls();
    printMenuHeader(highscores);
    printOptions(currentOption);
}

void printMenuHeader(char highscores[3][10])
{
    print_c_s("////////////////////////////////////////////////////////////////// \n"
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
    print_style("\nYour Highscores:\n", BOLD);
    printf("    Easy: %s\n    Medium: %s\n    Hard: %s\n", highscores[0], highscores[1], highscores[2]);
    print_style("\nPress h for help\n", ITALIC);
    print_line(LINE_LENGTH);

    printf("\n");
}

int handleMenu(char highscores[3][10])
{
    printMenuHeader(highscores);

    int inp = 0;
    int currentOption = 1; // 1 - 3
    printOptions(currentOption);

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
        case 10:
            return currentOption;
        case 'h':
        case 'H':
            printHelp(highscores, currentOption);
            break;
        default:
            break;
        }

        if (currentOption < 1)
            currentOption = 1;
        else if (currentOption > 3)
            currentOption = 3;
        printf("\x1b[4A");

        printOptions(currentOption);
    }
    return currentOption;
}

void spawnMines(Grid *grid)
{
    uint32_t totalPositions = grid->width * grid->height;
    grid->coveredTilesLeft = totalPositions - grid->totalMines;
    uint32_t totalMines = grid->totalMines;
    uint32_t width = grid->width;
    uint32_t height = grid->height;

    bool *excluded = calloc(totalPositions, sizeof(bool));
    if (!excluded)
        return;

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            int ny = (int)grid->current.y + dy;
            int nx = (int)grid->current.x + dx;
            if (ny >= 0 && ny < (int)height && nx >= 0 && nx < (int)width)
            {
                uint32_t index = ny * width + nx;
                excluded[index] = true;
            }
        }
    }

    uint32_t *positions = malloc(totalPositions * sizeof(uint32_t));
    if (!positions)
    {
        free(excluded);
        return;
    }

    uint32_t validCount = 0;
    for (uint32_t i = 0; i < totalPositions; i++)
    {
        if (!excluded[i])
        {
            positions[validCount++] = i;
        }
    }
    free(excluded);

    // Fisher-Yates shuffle
    for (uint32_t i = 0; i < totalMines && i < validCount; i++)
    {
        uint32_t j = i + rand() % (validCount - i);
        uint32_t temp = positions[i];
        positions[i] = positions[j];
        positions[j] = temp;
    }

    // Set mines
    for (uint32_t i = 0; i < totalMines; i++)
    {
        uint32_t x = positions[i] % width;
        uint32_t y = positions[i] / width;
        grid->tiles[y][x].isMine = true;

        for (int dy = -1; dy <= 1; dy++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                if (dy == 0 && dx == 0)
                    continue;

                int ny = (int)y + dy;
                int nx = (int)x + dx;
                if (ny >= 0 && ny < (int)grid->height && nx >= 0 && nx < (int)grid->width)
                {
                    grid->tiles[ny][nx].value++;
                }
            }
        }

        printf("Set Tile X: %u, Y: %u to mine\n", x, y);
    }
    free(positions);
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
    grid.minesPlaced = false;
    grid.coveredTilesLeft = width * height;

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
            grid.tiles[y][x].value = 0;
        }
    }

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
                int hl_index = color_to_ansi256((Color){0, 0, 0});
                int bg_index = color_to_ansi256_bg((Color){100, 255, 100});
                if (grid->tiles[y][x].uncovered == true)
                    sprintf(buffer, "\x1b[38;5;%dm\x1b[48;5;%dm%d\x1b[0m", hl_index, bg_index, grid->tiles[y][x].value);
                else
                    sprintf(buffer, "\x1b[38;5;%dm\x1b[48;5;%dm \x1b[0m", fg_index, bg_index);
                addTextToCache(buffer);
            }
            else if (grid->tiles[y][x].uncovered == true)
            {
                char buffer[60];
                int fg_index = color_to_ansi256((Color){255, 255, 255});
                int bg_index = color_to_ansi256_bg((Color){0, 0, 0});
                sprintf(buffer, "\x1b[38;5;%dm\x1b[48;5;%dm%d\x1b[0m", fg_index, bg_index, grid->tiles[y][x].value);
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
                int bg_index = color_to_ansi256_bg((Color){30, 30, 30});
                sprintf(buffer, "\x1b[38;5;%dm\x1b[48;5;%dm \x1b[0m", fg_index, bg_index);
                addTextToCache(buffer);
            }
            addTextToCache(" ");
        }
        addTextToCache("\n\n");
    }
    printCache();
}

void revealZeroTiles(Grid *grid, Pos pos)
{
    if (!grid->tiles)
        return;

    if (pos.y >= grid->height || pos.x >= grid->width)
        return;

    uint32_t max = grid->width * grid->height;
    Pos *stack = malloc(max * sizeof(Pos));
    if (!stack)
        return;

    uint32_t top = 0;
    stack[top++] = pos;

    while (top > 0)
    {
        Pos current = stack[--top];
        Tile *tile = &grid->tiles[current.y][current.x];

        if (tile->isMine || tile->flagged)
            continue;

        if (!tile->uncovered)
        {
            tile->uncovered = true;
            grid->coveredTilesLeft--;
        }

        if (tile->value != 0)
            continue;

        for (int dy = -1; dy <= 1; dy++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                if (dx == 0 && dy == 0)
                    continue;

                int ny = (int)current.y + dy;
                int nx = (int)current.x + dx;

                if (ny < 0 || ny >= (int)grid->height || nx < 0 || nx >= (int)grid->width)
                    continue;

                Tile *neighbor = &grid->tiles[ny][nx];

                if (neighbor->flagged || neighbor->uncovered)
                    continue;

                neighbor->uncovered = true;
                grid->coveredTilesLeft--;

                if (neighbor->value == 0 && top < max)
                    stack[top++] = (Pos){.x = (uint32_t)nx, .y = (uint32_t)ny};
            }
        }
    }

    free(stack);
}

int handleGame(Grid grid)
{
    time_t startTime = time(NULL);
    int elapsedSeconds = 0;
    bool running = true;

    while (running == true)
    {
        cls();

        time_t currentTime = time(NULL);
        elapsedSeconds = (int)difftime(currentTime, startTime);
        char timeString[9];
        secondsToHours(elapsedSeconds, timeString);
        printf("Time: %s\n", timeString);

        renderGrid(&grid);
        char inp = getch();
        switch (inp)
        {
        case 'W':
        case 'w': // Up
            if (grid.current.y > 0)
                grid.current.y -= 1;
            break;
        case 'S':
        case 's': // Down
            grid.current.y += 1;
            if (grid.current.y > grid.height - 1)
                grid.current.y = grid.height - 1;
            break;
        case 'A':
        case 'a': // Left
            if (grid.current.x > 0)
                grid.current.x -= 1;
            break;
        case 'D':
        case 'd': // Right
            grid.current.x += 1;
            if (grid.current.x > grid.width - 1)
                grid.current.x = grid.width - 1;
            break;
        case 13:
        case 10:
            if (grid.minesPlaced == false)
            {
                spawnMines(&grid);
                grid.minesPlaced = true;
            }
            if (!grid.tiles[grid.current.y][grid.current.x].uncovered)
            {
                grid.tiles[grid.current.y][grid.current.x].uncovered = true;
                grid.coveredTilesLeft--;
            }
            if (grid.tiles[grid.current.y][grid.current.x].value == 0)
                revealZeroTiles(&grid, grid.current);
            if (grid.tiles[grid.current.y][grid.current.x].isMine == true)
            {
                return -1;
            }
            break;
        case 8:
        case 127:
            grid.tiles[grid.current.y][grid.current.x].flagged = !grid.tiles[grid.current.y][grid.current.x].flagged;
            break;
        case 'q':
        case 'Q':
            running = false; // Exit game
            return -2;
        default:
            break;
        }
        if (grid.coveredTilesLeft == 0)
        {
            running = false;
        }
    }
    return elapsedSeconds;
}
#endif