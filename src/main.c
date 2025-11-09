#include "libs/game.h"
#include "libs/lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int time = 0; // positive = won and time; -1: lost; -2: quit
    while (time != -2)
    {
        cls();
        int mode = handleMenu();
        Grid grid = generateGridRandom(mode);

        time = handleGame(grid);
        switch (time)
        {
        case -2:
            return EXIT_SUCCESS;
        case -1:
            printf("You lost!");
            break;
        default:
            char timeString[10];
            secondsToHours(time, timeString);
            printf("You won! \nTime: %s", timeString);
            getch();
            break;
        }

        freeGrid(&grid);
    }
    getch();
    return EXIT_SUCCESS;
}