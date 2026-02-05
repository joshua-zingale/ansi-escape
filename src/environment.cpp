#include <iostream>


// Source - https://stackoverflow.com/a/62485211
// Posted by ProjectPhysX, modified by community. See post 'Timeline' for change history
// Retrieved 2026-02-04, License - CC BY-SA 4.0
// Modiified by Joshua Zingale

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <sys/ioctl.h>
#endif // Windows/Linux/Apple

int get_terminal_size(int *width, int *height) {
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi) != 0) {
        return 1;
    }
    *width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
    *height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
    return 0;
#elif defined(__linux__) || defined(__APPLE__)
    struct winsize w;
    if (ioctl(fileno(stdout), TIOCGWINSZ, &w) != 0) {
        return 1;
    }
    *width = (int)(w.ws_col);
    *height = (int)(w.ws_row);
    return 0;
#endif // Windows/Linux/Apple
return 1;
}