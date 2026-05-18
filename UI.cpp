#include "UI.h"

#include <iostream>
#include <string>

// make line
void separator(){
    std::cout << "============================================================" << std::endl;
}

// make space
void space(){ std::cout << "\n\n"; }

// print current user name
void currentuser(std::string username){
    std::cout << username << std::endl;
}

// print header
// print username if user is log in
// print message if message is not empty
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
