#include <iostream>
//#include <fstream>
#include <string>
#include "UI.h"
#include "Commands.h"
#include "Datastructures.h"
//#include "Email.h"
#include <windows.h>

LONG WINAPI NoDumpFilter(EXCEPTION_POINTERS* p){
    ExitProcess(1);
    return EXCEPTION_EXECUTE_HANDLER;
}

int main(){

    SetUnhandledExceptionFilter(NoDumpFilter);
    SetErrorMode(
        SEM_FAILCRITICALERRORS |
        SEM_NOGPFAULTERRORBOX |
        SEM_NOOPENFILEERRORBOX
    );

    std::cout << "\033[0m";
    auto data = datastructures();
    auto cmds = create_cmds(data);

    std::string pageTitle = "WELCOME TO THE MAIL SYSTEM";
    pageHeader(pageTitle, data.get_current_user().username);

    std::string line;
    std::cout << "Enter command (type 'quit' to exit)" << std::endl;

    while (getline(std::cin, line)){
        pageHeader(pageTitle, data.get_current_user().username);

        if (line == "quit") break;

        bool matched = false;

        for (auto& cmd : cmds) {
            std::smatch match;
            if(regex_match(line, match, cmd.pattern)){
                cmd.handler(match);
                matched = true;
                break;
            }
        }

        if (!matched){
            std::cout << "Invalid command" << std::endl;
        }
    }

    std::cout << "\033[0m";
    system("cls");
    return 0;
}
