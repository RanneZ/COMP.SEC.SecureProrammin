#include "Input.h"
#include <iostream>
#include <string>
#include "Validation.h"

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

std::string askUserName(){
    std::string line;
    std::cout << "Username: ";

    while (getline(std::cin, line)){
        if (!validateUserName(line)){
            std::cout << "Invalid username (containe one or more unalowed charater)" << std::endl;
        } else {
            break;
        }
        std::cout << "Username: ";
    }
    return line;
}

std::string askPassword(const std::string& username){
    std::string line;

    while(true){
        std::cout << "Password: ";
        line = passInput();

        if(line == "quit")return line;

        if(checkPass(line, username)){
            break;
        }
    }
    return line;
}

std::string reaskPassword(const std::string& password){
    std::string line;

    while(true){
        std::cout << "Confirm Password: ";
        line = passInput();

        if(line == "quit")return line;

        if(checkPasswordsMatches(password, line)){
            break;
        }
    }
    return line;
}
