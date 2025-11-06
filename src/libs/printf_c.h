#ifndef PRINTF_C_H
#define PRINTF_C_H

#include <stdio.h>
#include <math.h>

typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

int rgb_to_ansi256(Color color)
{
    int r_level = (int)round(color.r / 255.0 * 5.0);
    int g_level = (int)round(color.g / 255.0 * 5.0);
    int b_level = (int)round(color.b / 255.0 * 5.0);

    int ansi_index = 16 + (r_level * 36) + (g_level * 6) + b_level;
    return ansi_index;
}

void printf_c(const char *text, Color color){
    int index = rgb_to_ansi256(color);
    printf("\x1b[38;5;%dm", index);
    printf("%s", text);
    printf("\x1b[0m");
}

#endif
