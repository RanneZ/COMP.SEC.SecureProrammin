#include "input.h"
#include <iostream>
#include <conio.h>

std::string passInput(){
    std::string input;
    char c;

    // '\r' is ENTER
    // '\b' is BACKSPACE

    while ((c = _getch()) != '\r') {
        if (c == '\b') {
            if(!input.empty()){
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
