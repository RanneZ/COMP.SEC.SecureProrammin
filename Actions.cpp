#include "Actions.h"
#include "SaveAndLoad.h"
#include "UI.h"
#include "Validation.h"
#include "Input.h"
#include "Cryp.h"
#include "Config.h"
#include "split.h"
#include "SecureClear.h"

#include <iostream>


//////////////////////////////////////////////////////////////////////
//      PUBLIC      //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


Actions::Actions(){
    users = loadUsers(USERSFILE);
    std::cout << "Load users" << std::endl;
    for (User& user : users){
        std::cout << "user: " << user.username << std::endl;
    }
}

Actions::~Actions(){
    saveUsers(USERSFILE, users);
}


//////////////////////////////////////////////////////////////////////
//      EMAIL      ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


// create email and then sends it
void Actions::createEmail(){
    if(!isLogIn()) return;

    std::cout << "(type 'back' to return at any point)" << std::endl;

    std::vector<std::string> validAddresess;
    std::vector<std::string> invalidAddresess;
    std::string input;
    char delimiter = ' ';

    std::cout << "Recipient(s) email address or contact name" << std::endl;
    std::cout << "Recipient(s): ";
    getline(std::cin, input);
    if(inputIsBack(input)) return;

    std::vector<std::string> addresess = split(input, delimiter, true);

    // short valid and invalid addresess
    for(const auto& address : addresess){
        if(validEmail(address)){
            validAddresess.push_back(address);
        } else if(validateUserName(address)){
            Contact contact = getContact(address);
            if(contact.email != ""){
                validAddresess.push_back(contact.email);
            } else {
                invalidAddresess.push_back(address);
            }
        } else {
            invalidAddresess.push_back(address);
        }
    }

    // subject
    space();
    std::string subject = inputSubject();
    if(inputIsBack(subject)) return;

    // message
    space();
    std::string message = inputMessage();
    if(inputIsBack(message)) return;

    emailContent content;
    content.from = currentUser.email;
    content.pass = emailPass;
    content.to = validAddresess; // change this to vector in struct
    content.subject = subject;
    content.message = message;

    // print all valid addresess and invalid addresess
    std::cout << "Email will be send to all these addresess" << std::endl;
    space();
    std::cout << "Valid addresess" << std::endl;
    for(const auto& item : validAddresess){
        std::cout << "+" << item << "+" << std::endl;
    }
    space();
    std::cout << "These were invalid addresses and the email will not be sent to them" << std::endl;
    space();
    std::cout << "invalid addresess" << std::endl;
    for(const auto& item : invalidAddresess){
        std::cout << "+" << item << "+" << std::endl;
    }
    space();

    std::cout << "Do you want to send the email?" << std::endl;
    input = inputYesOrNo();
    if(input == "n" || input == BACK){
        inputIsBack(BACK);
        return;
    }

    prepareEmail(content);
    return;
}


//////////////////////////////////////////////////////////////////////
//      CONTACT      /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


void Actions::createContact(){
    if(!isLogIn()) return;

    std::cout << "(type 'back' to return at any point)" << std::endl;

    Contact newContact;
    std::string input;

    // use username logic, may be update function name
    input = inputUsername();
    if(inputIsBack(input)) return;
    newContact.username = input;

    input = inputEmail();
    if(inputIsBack(input)) return;
    newContact.email = input;

    currentUser.contacts.push_back(newContact);
    // update database
    updateUsers();
    exitAction(newContact.username+" contact created!");
}

Contact Actions::getContact(std::string contactName){
    Contact contact;
    if(!isLogIn()) return contact;

    for (const auto& con : currentUser.contacts){
        if(con.username == contactName){
            contact = con;
            break;
        }
    }

    return contact;
}

void Actions::updateContact(const std::string& contactName){
    if(!isLogIn()) return;

    std::cout << "(type 'back' to return at any point)" << std::endl;
    space();

    Contact updatedContact;
    std::string input;

    for(auto& contact : currentUser.contacts){
        if(contact.username == contactName){

            std::cout << "Do you want to update contact name?" << std::endl;
            input = inputYesOrNo();
            if(inputIsBack(input)) return;
            if(input == "y"){
                input = inputUsername();
                if(inputIsBack(input)) return;
                updatedContact.username = input;
            }

            std::cout << "Do you want to update contact email?" << std::endl;
            input = inputYesOrNo();
            if(inputIsBack(input)) return;
            if(input == "y"){
                input = inputEmail();
                if(inputIsBack(input)) return;
                updatedContact.email = input;
            }

            if(updatedContact.username != ""){
                contact.username = updatedContact.username;
            }

            if(updatedContact.email != ""){
                contact.email = updatedContact.email;
            }

            // update database
            updateUsers();
            exitAction("Contact updated!");
            return;
        }   
    }
    exitAction("No contact founded!");
}

void Actions::removeContact(const std::string& contactName){
    if(!isLogIn()) return;

    auto& contacts = currentUser.contacts;

    for (auto contact = contacts.begin(); contact != contacts.end(); ++contact){
        if (contact->username == contactName){
            contacts.erase(contact);
            // update database
            updateUsers();
            exitAction(contactName+" found and removed");
            return;
        }
    }
    exitAction(contactName+" not found");
}

void Actions::printJustContacts(){
    if(!isLogIn()) return;

    exitAction("");
    printContacts();
}


//////////////////////////////////////////////////////////////////////
//      USER      ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


// not ready
void Actions::createNewUser(){
    User newUser;
    std::string input;
    std::string pass;
    std::string email;

    std::cout << "Create new user:" << std::endl;
    std::cout << "(type 'back' to return at any point)" << std::endl;
    space();

    // new user information request
    // ask username loop
    while(true){
        input = inputUsername();
        if(inputIsBack(input)) return;
        if(usernameAlreadyExist(input)) continue;

        break;
    }

    newUser.username = input;

    // ask password and reask to check if they matches
    input = inputPassword(newUser.username);
    if(inputIsBack(input)) return;
    pass = input;
    input = reinputPassword(pass);
    if(inputIsBack(input)) return;

    // hash and salt the password and store password hash and salt
    hashSalt newHashSalt = hashAndSaltPassword(pass);
    newUser.passwordHash = newHashSalt.hash;
    newUser.passwordSalt = newHashSalt.salt;

    input.clear();
    stringSecureClear(pass);

    // email, email app password and validation code loop
    int attemptsLeft = 5;
    while (true){
        if(attemptsLeft <= 0){
            exitAction("Too many attempts! Quiting sign in with new user");
            return;
        }

        std::cout << "++ attemps left: " << attemptsLeft << " ++" << std::endl;
        attemptsLeft --;

        // ask email loop
        while(true){
            input = inputEmail();
            if(inputIsBack(input)) return;
            if(emailAlreadyExist(input)) continue;

            break;
        }
        email = input;

        // ask email app password
        input = inputEmailAppPassword(newUser.username);
        if(inputIsBack(input)) return;

        pass = input;
        std::cout << input << std::endl;

        ReturnStatus status = emailCodeValidation(email, pass);
        if(status == QUIT){
            exitAction("");
            return;
        } else if(status == AUTHFAIL) {
            exitAction("Authentication failure! Email and/or emails app password is wrong");
            continue;
        } else if(status == CODEFAIL) {
            exitAction("Too many attempts! Quiting sign in with new user");
            return;
        }

        stringSecureClear(pass);
        break;
    }


    newUser.email = email;

    users.push_back(newUser);

    if(saveUsers(USERSFILE, users)){
        exitAction("You have succesfully sign in! \n (type 'log_in "+newUser.username+"' if you want to log in)");
    }
    else {
        exitAction("Sign in has failed! \n (type 'sign_in' if you want to try again)");
    }

}


void Actions::logInUser(std::string usernameOrEmail)
{
    bool isEmail;
    std::string input;
    std::string pass;
    User userTemp;

    if(currentUser.username != ""){
        logOutUser();
    }

    // check if username or email exist
    if (validEmail(usernameOrEmail)){
        isEmail = true;
    } else if (validateUserName(usernameOrEmail)){
        isEmail = false;
    } else {
        exitAction("\nNot valid username or email. Please try again type 'log_in <valid username or email>'\n");
        return;
    }

    std::cout << "Please Log in " << usernameOrEmail << " by providing password\n";

    while(true){
        std::cout << "Password: ";
        input = hiddenInput();

        if(inputIsBack(input))return;

        if(!checkPassLength(input)){
            std::cout << "Too long or too short password!" << std::endl;
        } else {
            pass = input;
            break;
        }
    }

    if(isEmail){
        for (User& user : users) {
            if (user.email == usernameOrEmail){
                userTemp = user;
                break;
            }
        }

        if(userTemp.email != usernameOrEmail){
            exitAction("log in has failed! wrong username or password");
            return;
        }
    } else {
        for (User& user : users) {
            if (user.username == usernameOrEmail){
                userTemp = user;
                break;
            }
        }

        if(userTemp.username != usernameOrEmail){
            exitAction("log in has failed! wrong username or password");
            return;
        }
    }

    hashSalt userHashSalt = {userTemp.passwordHash, userTemp.passwordSalt};

    if(authenticate(pass, userHashSalt)){
        currentUser = userTemp;
        exitAction("Log in successfully "+currentUser.username);
    } else {
        exitAction("log in has failed! wrong username or password");
    }

    stringSecureClear(pass);
}

void Actions::changePassword(){
    if(!isLogIn()) return;

    std::string input;
    std::string pass;


    // ask password and reask to check if they matches
    input = inputPassword(currentUser.username);
    if(inputIsBack(input)) return;
    pass = input;
    input = reinputPassword(pass);
    if(inputIsBack(input)) return;

    // hash and salt the password and store password hash and salt
    hashSalt newHashSalt = hashAndSaltPassword(pass);
    stringSecureClear(pass);

    int attemptsLeft = 5;
    while (true){
        if(attemptsLeft <= 0){
            exitAction("Too many attempts! Quiting change password");
            return;
        }

        std::cout << "++ attemps left: " << attemptsLeft << " ++" << std::endl;
        attemptsLeft --;

        if(emailPass == ""){
            pass = requestEmailPass();
        } else {
            pass = emailPass;
        }

        ReturnStatus status = emailCodeValidation(currentUser.email, pass);
        if(status == QUIT){
            exitAction("");
            return;
        } else if(status == AUTHFAIL) {
            std::cout << "+ Authentication failure! Email and/or emails app password is wrong +" << std::endl;
            continue;
        } else if(status == CODEFAIL) {
            exitAction("Too many attempts! Quiting change password");
            return;
        }

        if(emailPass == ""){
            emailPass = pass;
        }
        break;
    }

    currentUser.passwordHash = newHashSalt.hash;
    currentUser.passwordSalt = newHashSalt.salt;

    // update database
    updateUsers();

    space();
    std::cout << "Password has been changed successfully" << std::endl;
    space();
}

void Actions::changeEmailAddress(){
    if(!isLogIn()) return;

    std::string input;
    std::string pass;

    // ask email loop
    while(true){
        input = inputEmail();
        if(inputIsBack(input)) return;
        if(emailAlreadyExist(input)) continue;

        break;
    }

    int attemptsLeft = 5;
    while (true){
        if(attemptsLeft <= 0){
            exitAction("Too many attempts! Quiting change email address");
            return;
        }

        std::cout << "++ attemps left: " << attemptsLeft << " ++" << std::endl;
        attemptsLeft --;

        if(emailPass == ""){
            pass = requestEmailPass();
        } else {
            pass = emailPass;
        }

        ReturnStatus status = emailCodeValidation(currentUser.email, pass);
        if(status == QUIT){
            exitAction("");
            return;
        } else if(status == AUTHFAIL) {
            std::cout << "+ Authentication failure! Email and/or emails app password is wrong +" << std::endl;
            continue;
        } else if(status == CODEFAIL) {
            exitAction("Too many attempts! Quiting change email address");
            return;
        }

        if(emailPass == ""){
            emailPass = pass;
        }
        break;
    }

    stringSecureClear(pass);

    // update database
    updateUsers();

    space();
    std::cout << "Email has been changed successfully" << std::endl;
    space();

}

void Actions::logOutUser(){
    if(!isLogIn())return;

    User user;
    currentUser = user;
    stringSecureClear(emailPass);
    exitAction("Log out successfully");
    return;
}

void Actions::printUserInfo(){
    if(!isLogIn()) return;

    exitAction("");
    std::cout << ">> User information <<" << std::endl;

    std::cout << "Username: " << currentUser.username << std::endl;
    std::cout << "Email: " << currentUser.email << std::endl << std::endl;
    printContacts();
    return;
}


//////////////////////////////////////////////////////////////////////
//      GETTER      //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


User Actions::getCurrentUser(){
    return currentUser;
}


//////////////////////////////////////////////////////////////////////
//      PRIVATE     //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


void Actions::printContacts(){

    if(currentUser.contacts.size() <= 0){
        std::cout << "No cantacts yet. \ntype 'create_contact' to create first contact" << std::endl;
        return;
    }

    std::cout << "User contacts:" << std::endl;
    for(const auto& contact : currentUser.contacts){
        space();
        std::cout << contact.username << std::endl;
        std::cout << contact.email << std::endl;
    }
    return;
}

// send email if email app password (emailPass) has password
void Actions::prepareEmail(emailContent& content){

    std::string input;

    // ask first time to request email app password after log in
    if(content.pass == ""){
        input = requestEmailPass();
        if(inputIsBack(input)) return;

        content.pass = input;
    }

    if(!sendEmail(content)){
        exitAction("Email authentication failed");
    } else {
        if(emailPass == ""){
            emailPass = input;
        }

        exitAction("Email has send successfully");
    }
}

std::string Actions::requestEmailPass(){
    std::string input = inputEmailAppPassword(currentUser.username);
    if(input == BACK) return input;
    return input;
}

bool Actions::usernameAlreadyExist(const std::string& username){

    for (User& user : users) {
        if (user.username == username){
            std::cout << "+ Username not accepted. Username already in use. +" << std::endl;
            return true;
        }
    }

    return false;
}

bool Actions::emailAlreadyExist(const std::string& email){
    for (User& user : users) {
        if (user.email == email){
            std::cout << "+ Email not accepted. Email already in use. +" << std::endl;
            return true;
        }
    }

    return false;
}

bool Actions::isLogIn(){
    if(currentUser.username == ""){
        pageHeader("WELCOME TO THE MAIL SYSTEM", getCurrentUser().username,
                   "+ User is not log in. +\n+ Log in by 'log_in <username or email>' +\n+ or sign in by 'sign_in' +");
        return false;
    }
    return true;
}

// update users and save it
void Actions::updateUsers(){
    for(User& user : users){
        if(currentUser.username == user.username){
            user.email = currentUser.email;
            user.passwordHash = currentUser.passwordHash;
            user.passwordSalt = currentUser.passwordSalt;
            user.contacts = currentUser.contacts;
            break;
        }
    }
    saveUsers(USERSFILE, users);
}

void Actions::exitAction(const std::string &message){
    pageHeader("WELCOME TO THE MAIL SYSTEM", getCurrentUser().username, message);
    return;
}

bool Actions::inputIsBack(std::string input){
    if(input == BACK){
        exitAction("");
        return true;
    }
    return false;
}
