#include <unistd.h>
#include <stdio.h>

size_t utilClearScreen(void) {
    const char *clear_screen_ansi = "\e[1;1H\e[2J";
    return write(STDOUT_FILENO, clear_screen_ansi, sizeof(clear_screen_ansi));
}
