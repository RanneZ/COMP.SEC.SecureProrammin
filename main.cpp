#include "UI.h"
#include "Commands.h"
#include "Actions.h"
#include "Config.h"

#include <iostream>
#include <string>
#include <QCoreApplication>

int main(int argc, char *argv[]){

    // Force the app to look for plugins right next to the .exe
    // (desperate fix i know but it works)
    QCoreApplication::addLibraryPath(".");
    qputenv("QT_SSL_BACKEND", "schannel");

    try{
        // change console print color to defoult
        std::cout << "\033[0m";

        // create actions
        auto act = Actions();

        // create commands
        auto cmds = createCmds(act);

        std::string pageTitle = "WELCOME TO THE MAIL SYSTEM";
        pageHeader(pageTitle, act.getCurrentUser().username, "");

        std::string line;
        std::cout << "Enter command (type 'exit' to exit or 'help' to see list of commands)" << std::endl;

        // main loop
        while (getline(std::cin, line)){
            pageHeader(pageTitle, act.getCurrentUser().username, "");

            if (line == EXIT) break;

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

        // change console print color to defoult
        std::cout << "\033[0m";
        system("cls");
        return 0;

    } catch (const std::exception& e) {
        // change console print color to defoult
        std::cout << "\033[0m";

        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}
