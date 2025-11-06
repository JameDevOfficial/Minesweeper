#include "libs/game.h"
#include "libs/lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint32_t x;
    uint32_t y;
} bomb;

typedef struct
{
    uint32_t width;
    uint32_t height;
    uint32_t totalBombs;
    bomb bombs[];
} Grid;

int main()
{
    print_menu();
}
