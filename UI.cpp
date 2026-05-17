#include "UI.h"

#include <iostream>
#include <string>

void cursor(){ std::cout << ">>> "; }

void separator(){
    std::cout << "============================================================" << std::endl;
}

void margin(){ std::cout << "     "; }

void date(){
    std::cout << "                                                  00.00.0000" << std::endl;
}

void space(){ std::cout << "\n\n"; }

void currentuser(std::string username){
    std::cout << username << std::endl;
}

void pageHeader(const std::string& pageTitle, const std::string& username, const std::string& message){
    system("cls");
    if(username != "")currentuser(username);
    std::cout << pageTitle << std::endl;
    separator();
    std::cout << std::endl;
    if(message != ""){
        std::cout << message << std::endl;
    }
}
