#ifndef PRINTF_C_H
#define PRINTF_C_H

#include <stdio.h>
#include <math.h>

/// @brief Text Styles Ansii Values
typedef enum {
    RESET = 0,
    BOLD = 1,
    FAINT = 2,
    ITALIC = 3,
    UNDERLINE = 4,
    BLINK_SLOW = 5,
    BLINK_FAST = 6,
    INVERTED = 7,
    INVISIBLE = 8,
    STRIKETHROUGH = 9,
} TextStyle;

/// @brief Color with red, green, blue
typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

/// @brief Color to Ansii index
/// @param color The color to convert with r, g, b
/// @return Ansii index of the color
int color_to_ansi256(Color color)
{
    int r_level = (int)round(color.r / 255.0 * 5.0);
    int g_level = (int)round(color.g / 255.0 * 5.0);
    int b_level = (int)round(color.b / 255.0 * 5.0);

    int ansi_index = 16 + (r_level * 36) + (g_level * 6) + b_level;
    return ansi_index;
}

/// @brief printf with color
/// @param text the char[] (String) to print
/// @param color the color in which to print
void printf_c(const char *text, Color color){
    int index = color_to_ansi256(color);
    printf("\x1b[38;5;%dm", index);
    printf("%s", text);
    printf("\x1b[0m");
}

/// @brief printf with color and style
/// @param text the char[] (String) to print
/// @param color the color in which to print
/// @param style the style in which to print from TextStyle
void printf_c_s(const char *text, Color color, TextStyle style)
{
    int index = color_to_ansi256(color);
    printf("\x1b[%dm", style);
    printf("\x1b[38;5;%dm", index);
    printf("%s", text);
    printf("\x1b[0m");
}

/// @brief printf with color and multiple styles
/// @param text the char[] (String) to print
/// @param color the color in which to print
/// @param styles the styles in which to print from TextStyle[]
/// @param stylesTotal the total amount of styles
void printf_c_ms(const char *text, Color color, TextStyle *styles, int stylesTotal)
{
    int index = color_to_ansi256(color);
    for (int i = 0; i < stylesTotal; i++)
    {
        printf("\x1b[%dm", styles[i]);
    }
    printf("\x1b[38;5;%dm", index);
    printf("%s", text);
    printf("\x1b[0m");
}
#endif
