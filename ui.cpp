#include "ui.h"
#include <iostream>
#include <string>
#include "Config.h"

void cursor(){ std::cout << ">>> "; }

void separator(){
    std::cout << "============================================================" << std::endl;
}

void margin(){ std::cout << "     "; }

void version(){
    std::cout << "                                               " << VERSION << std::endl;
}

void date(){
    std::cout << "                                                  00.00.0000" << std::endl;
}

void space(){ std::cout << "\n\n"; }

void currentuser(std::string username){
    std::cout << username << std::endl;
}

void pageHeader(const std::string& pageTitle, const std::string& username){
    system("cls");
    version();
    if(username != "")currentuser(username);
    std::cout << pageTitle << std::endl;
    separator();
    std::cout << std::endl;
}
