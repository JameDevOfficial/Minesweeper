#include "libs/game.h"
#include "libs/lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define HIGHSCORE_FILE "highscore.txt"

int main()
{
    int highscore = 0;
    char highscoreString[10];
    FILE *fp = fopen(HIGHSCORE_FILE, "rb"); 
    if (fp)
    {
        fread(&highscore, sizeof(int), 1, fp);
        fclose(fp);
    }
    secondsToHours(highscore, highscoreString);

    srand(time(NULL));
    int time = 0; // positive = won and time; -1: lost; -2: quit
    while (time != -2)
    {
        cls();
        int mode = handleMenu(highscoreString);
        if (mode == -2)
            return EXIT_SUCCESS;
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
            printf("You won! \nTime: %s\n", timeString);
            if (highscore == 0 || highscore > time)
            {
                highscore = time;
                secondsToHours(highscore, highscoreString);
                printf("New highscore!\n");

                FILE *fp = fopen(HIGHSCORE_FILE, "wb");
                if (fp)
                {
                    fwrite(&highscore, sizeof(int), 1, fp);
                    fclose(fp);
                }
            }
            getch();
            break;
        }

        freeGrid(&grid);
    }
    getch();
    return EXIT_SUCCESS;
}