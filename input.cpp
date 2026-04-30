#include "input.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
char getch_wrapper() {
    return _getch();
}
#else
#include <termios.h>
#include <unistd.h>

char getch_wrapper() {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO); // disable buffering + echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char c = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore
    return c;
}
#endif

std::string passInput() {
    std::string input;
    char c;

    while ((c = getch_wrapper()) != '\n' && c != '\r') {
        if (c == 127 || c == '\b') {
            if (!input.empty()) {
                input.pop_back();
                std::cout << "\b \b";
            }
        } else {
            input.push_back(c);
            std::cout << '*';
        }
    }

    std::cout << std::endl;
    return input;
}
