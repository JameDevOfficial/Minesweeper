#ifndef PRINTF_C_H
#define PRINTF_C_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int getch(void)
{
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
#endif

void clearCache();



/// @brief Text Styles Ansii Values
typedef enum
{
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
typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

/// @brief Clear the console screen (platform independent)
void cls()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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

/// @brief Color to Ansii index for background
/// @param color The color to convert with r, g, b
/// @return Ansii index of the color for background
int color_to_ansi256_bg(Color color)
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
void print_c(const char *text, Color color)
{
    int index = color_to_ansi256(color);
    printf("\x1b[38;5;%dm", index);
    printf("%s", text);
    printf("\x1b[0m");
}

/// @brief printf with color and style
/// @param text the char[] (String) to print
/// @param color the color in which to print
/// @param style the style in which to print from TextStyle
void print_c_s(const char *text, Color color, TextStyle style)
{
    int index = color_to_ansi256(color);
    printf("\x1b[%dm", style);
    printf("\x1b[38;5;%dm", index);
    printf("%s", text);
    printf("\x1b[0m");
}

/// @brief printf with style
/// @param text the char[] (String) to print
/// @param style the style in which to print from TextStyle
void print_style(const char *text, TextStyle style)
{
    printf("\x1b[%dm", style);
    printf("%s", text);
    printf("\x1b[0m");
}

/// @brief printf with color and multiple styles
/// @param text the char[] (String) to print
/// @param color the color in which to print
/// @param styles the styles in which to print from TextStyle[]
/// @param stylesTotal the total amount of styles
void print_c_ms(const char *text, Color color, TextStyle *styles, int stylesTotal)
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

/// @brief printf with foreground and background color
/// @param text the char[] (String) to print
/// @param fg_color the foreground color
/// @param bg_color the background color
void print_c_bg(const char *text, Color fg_color, Color bg_color)
{
    int fg_index = color_to_ansi256(fg_color);
    int bg_index = color_to_ansi256_bg(bg_color);
    printf("\x1b[38;5;%dm", fg_index);
    printf("\x1b[48;5;%dm", bg_index);
    printf("%s", text);
    printf("\x1b[0m");
}

/// @brief printf with foreground, background color and style
/// @param text the char[] (String) to print
/// @param fg_color the foreground color
/// @param bg_color the background color
/// @param style the style in which to print from TextStyle
void print_c_bg_s(const char *text, Color fg_color, Color bg_color, TextStyle style)
{
    int fg_index = color_to_ansi256(fg_color);
    int bg_index = color_to_ansi256_bg(bg_color);
    printf("\x1b[%dm", style);
    printf("\x1b[38;5;%dm", fg_index);
    printf("\x1b[48;5;%dm", bg_index);
    printf("%s", text);
    printf("\x1b[0m");
}

/// @brief printf with foreground, background color and multiple styles
/// @param text the char[] (String) to print
/// @param fg_color the foreground color
/// @param bg_color the background color
/// @param styles the styles in which to print from TextStyle[]
/// @param stylesTotal the total amount of styles
void print_c_bg_ms(const char *text, Color fg_color, Color bg_color, TextStyle *styles, int stylesTotal)
{
    int fg_index = color_to_ansi256(fg_color);
    int bg_index = color_to_ansi256_bg(bg_color);
    for (int i = 0; i < stylesTotal; i++)
    {
        printf("\x1b[%dm", styles[i]);
    }
    printf("\x1b[38;5;%dm", fg_index);
    printf("\x1b[48;5;%dm", bg_index);
    printf("%s", text);
    printf("\x1b[0m");
}

/// @brief print a line with custom length
/// @param length will print "-" n times
void print_line(int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("-");
    }
}

/// @brief print a line with custom length and symbol
/// @param length will print symbol n times
/// @param symbol symbol for line
void print_line_s(int length, char symbol)
{
    for (int i = 0; i < length; i++)
    {
        printf("%c", symbol);
    }
}

#define CACHE_SIZE 50000
static char textCache[CACHE_SIZE] = {0};
static int cachePosition = 0;

/// @brief Add text to the cache buffer
/// @param text the text to add to cache
void addTextToCache(char *text)
{
    int length = strlen(text);

    if (cachePosition + length < CACHE_SIZE - 1)
    {
        memcpy(textCache + cachePosition, text, length);
        cachePosition += length;
    }
    else
    {
        fprintf(stderr, "Text cache is full!\n");
    }
}

/// @brief Print all cached text and clear the cache
void printCache()
{
    if (cachePosition > 0)
    {
        fwrite(textCache, 1, cachePosition, stdout);
        fflush(stdout);
        clearCache();
    }
}

/// @brief Clear the text cache without printing
void clearCache()
{
    cachePosition = 0;
    textCache[0] = '\0';
}

void secondsToHours(int seconds, char *string){
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int sec = seconds % 60;
    sprintf(string, "%02d:%02d:%02d", hours, minutes, sec);
}

#endif
