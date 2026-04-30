#ifndef UTILITY_H
#define UTILITY_H
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <conio.h>

using namespace std;

enum Validate {YES, NO, CONTINUE};

string VERSION = "v.0.0.2.alpha";

void cursor(){
    cout << ">>> ";
}

void separet(){
    cout << "============================================================" << endl;
}

void marginal(){
    cout << "     ";
}

void versio(){
    cout << "                                               " << VERSION << endl;
}

void date(){
    cout << "                                                  00.00.0000" << endl;
}

void space(){
    cout << "\n\n";
}

void textField(string text){

}

void pageHeader(string pageTitle){
    system("cls");
    versio();
    cout << pageTitle << endl;
    separet();
    cout << endl;
}

Validate exit(string input){
    if (input == "EXIT" || input == "exit" || input == "e" ){
        cout << "Do you want to EXIT program? y/n" << endl;
        cursor();
        cin >> input;
        if (input == "y"){
            return YES;
        } else return NO;
    }
    return CONTINUE;
}

bool logout(string input){
    if (input == "LOGOUT" || input == "logout" || input == "l" ){
        cout << "Do you want to LOGOUT current user? y/n" << endl;
        cursor();
        cin >> input;
        if (input == "y"){
            return true;
        } else return false;
    }
    return false;
}

string commandInput(){
    string userInput;
    try {
        cin >> userInput;
    } catch (...) {

    }
    return userInput;
}

bool validEmail(string email){
    // OWASP Input Validation/Email Address Validation
    // https://cheatsheetseries.owasp.org/cheatsheets/Input_Validation_Cheat_Sheet.html#email-address-validation

    size_t atPosition = email.find('@');
    if (atPosition == string::npos) return false;

    string local = email.substr(0, atPosition);
    string domain = email.substr(atPosition + 1);

    if(local.length() > 63 || email.length() > 254) return false;

    regex localPattern("^[a-z0-9-]+(\\.[a-z0-9-])*$");
    regex domainPattern("^([a-z0-9]+(-[a-z0-9]+)*\\.)+[a-z]{2,}$");

    if(!regex_match(local, localPattern)) return false;
    if(!regex_match(domain, domainPattern)) return false;

    return true;
}

string emailInput(){

    string userInput;
    cin >> userInput;

    if(validEmail(userInput)) return "NOT VALID";

    return userInput;
}

bool checkPassLength (string password){
    if (password.length() < 8 || password.length() > 64) return false;
    return true;
}

string passInput(){

    string userInput;
    char c;

    while ((c = _getch()) != '\r') {
        if (c == '\b') {
            if(!userInput.empty()){
                userInput.pop_back();
            }
        } else {
            userInput.push_back(c);
        }
    }

    return userInput;
}

#endif // UTILITY_H
