#include "libs/game.h"
#include "libs/lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define HIGHSCORE_FILE "highscore.txt"

int main()
{
    int highscores[3] = {0};
    char highscoreStrings[3][10];
    FILE *fp = fopen(HIGHSCORE_FILE, "rb"); 
    if (fp)
    {
        fread(&highscores, sizeof(int), 3, fp);
        fclose(fp);
    }
    secondsToHours(highscores[0], highscoreStrings[0]);
    secondsToHours(highscores[1], highscoreStrings[1]);
    secondsToHours(highscores[2], highscoreStrings[2]);

    srand(time(NULL));
    int gameTime = 0; // positive: won and time; -1: lost; -2: quit
    while (gameTime != -2)
    {
        cls();
        int mode = handleMenu((char(*)[10])highscoreStrings);

        if (mode == -2)
            return EXIT_SUCCESS;
        Grid grid = generateGridRandom(mode);

        gameTime = handleGame(grid);
        switch (gameTime)
        {
        case -2:
            return EXIT_SUCCESS;
        case -1:
            print_c_s("You lost!\n", (Color){255, 50, 50}, BOLD);
            getch();
            break;
        default:
            char timeString[10];
            secondsToHours(gameTime, timeString);
            print_c_s("You won! ", (Color){50, 255, 50}, BOLD);
            printf("\nTime: %s\n", timeString);
            int index = mode - 1;
            if (index < 0) return EXIT_FAILURE;
            if (highscores[index] == 0 || highscores[index] > gameTime)
            {
                highscores[index] = gameTime;
                secondsToHours(highscores[index], highscoreStrings[index]);
                printf("New highscore!\n");

                FILE *fp = fopen(HIGHSCORE_FILE, "wb");
                if (fp)
                {
                    fwrite(&highscores, sizeof(int), 3, fp);
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