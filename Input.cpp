// AI was used to crete hiddenInput and the getch_wrapper.
// ChatGPT (GPT-5.5.)

#include "Input.h"
#include "Validation.h"
#include "Config.h"

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

// hide the users input covering it with '*' character
std::string hiddenInput() {
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

std::string inputUsername(){
    std::string input;
    std::cout << "Username: ";

    while (getline(std::cin, input)){
        if (!validateUserName(input)){
            std::cout << "Invalid username (containe one or more unalowed charater)" << std::endl;
        } else {
            break;
        }
        std::cout << "Username: ";
    }
    return input;
}

std::string inputPassword(const std::string& username){
    std::string input;

    while(true){
        std::cout << "Password: ";
        input = hiddenInput();

        if(input == BACK)return input;

        if(checkPass(input, username)){
            break;
        }
    }
    return input;
}

std::string reinputPassword(const std::string& password){
    std::string input;

    while(true){
        std::cout << "Confirm Password: ";
        input = hiddenInput();

        if(input == BACK)return input;

        if(checkPasswordsMatches(password, input)){
            break;
        }
    }
    return input;
}


std::string inputEmail(){
    std::string input;
    std::cout << "Email: ";

    while (getline(std::cin, input)){
        if(input == BACK)return input;

        if (!validEmail(input)){
            std::cout << "Invalid email address!" << std::endl;
        } else {
            break;
        }
        std::cout << "Email: ";
    }
    return input;
}

std::string inputEmailAppPassword(const std::string& username){
    std::string input;

    while(true){
        std::cout << "Emails App Password: ";
        input = hiddenInput();

        if(input == BACK)return input;

        if(checkPass(input, username)){
            break;
        }
    }
    return input;
}

std::string inputSubject(){
    std::string line;
    std::cout << "Subject: ";

    while (getline(std::cin, line)){

        if(line == BACK)return line;

        if (!validateSubject(line)){
            std::cout << "Subject conteins ilegal characters like:" << std::endl;
            std::cout << "All control characters \\x00-\\x1F, DEL (\\x7F)," << std::endl;
            std::cout << "Carriage Return (\\r) and/or Newline (\\n)" << std::endl;
        } else {
            break;
        }
        std::cout << "Subject: ";
    }
    return line;

}

std::string inputMessage(){
    std::string line;
    std::cout << "Message: ";

    while (getline(std::cin, line)){

        if(line == BACK)return line;

        if (!validateMessage(line)){
            std::cout << "Message too long or conteins '\0' " << std::endl;
        } else {
            break;
        }
        std::cout << "Message: ";
    }
    return line;
}

std::string inputYesOrNo(){
    std::string input;
    std::cout << "y/n: ";

    while (getline(std::cin, input)){
        if (input == "y"){
            break;
        } else if (input == "n") {
            break;
        } else if (input == BACK){
            break;
        }
        std::cout << "Not valid answer type 'y' or 'n' ";
        std::cout << "y/n: ";
    }
    return input;

}
