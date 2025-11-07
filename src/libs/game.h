#ifndef GAME_H
#define GAME_H

#include "lib.h"
#include "stdbool.h"
#include <conio.h>

#define LINE_LENGTH 66
int handleGame(int difficulty);

typedef struct
{
    uint32_t x;
    uint32_t y;
} Mine;

typedef struct
{
    uint32_t width;
    uint32_t height;
    uint32_t totalBombs;
    Mine mines[];
} Grid;

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

int handleGame(int difficulty, Grid grid)
{
    cls();
    
}
#endif