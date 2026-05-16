#include "Datastructures.h"
#include "SaveAndLoad.h"
#include <iostream>
#include "UI.h"
#include "Validation.h"
#include "Input.h"
#include "Cryp.h"
#include "Config.h"


datastructures::datastructures(){
    users = loadUsers(USERSFILE);
    std::cout << "Load users" << std::endl;
    for (User& user : users){
        std::cout << "user: " << user.username << std::endl;
    }

}

datastructures::~datastructures(){
    saveUsers(USERSFILE, users);
}

// create email and then sends it
void datastructures::create_email(){
    if(!isSignIn()) return;

    std::vector<std::string> validAddresess;
    std::vector<std::string> invalidAddresess;
    std::string inputLine;
    char delimiter = ' ';

    std::cout << "Recipient(s) email address or contact name" << std::endl;
    std::cout << "Recipient(s): ";
    getline(std::cin, inputLine);
    if(inputLine == "quit") return;

    std::vector<std::string> addresess = datastructures::split(inputLine, delimiter, true);

    // short valid and invalid addresess
    for(auto address : addresess){
        if(validEmail(address)){
            validAddresess.push_back(address);
        } else if(validateUserName(address)){
            Contact contact = get_contact(address);
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
    std::string subject = askSubject();
    if(subject == "quit") return;

    // message
    space();
    std::string message = askMessage();
    if(message == "quit") return;

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
    for(auto item : validAddresess){
        std::cout << "+" << item << "+" << std::endl;
    }
    space();
    std::cout << "These were invalid addresses and the email will not be sent to them" << std::endl;
    space();
    std::cout << "invalid addresess" << std::endl;
    for(auto item : invalidAddresess){
        std::cout << "+" << item << "+" << std::endl;
    }
    space();

    std::cout << "Do you want to send the email?" << std::endl;
    inputLine = askYesOrNo();
    if(inputLine == "n" || inputLine == "quit") return;

    // lähetä
    send_email(content);

    return;
}

// send email if email app password (emailPass) has password
void datastructures::send_email(emailContent& content){
    // ask first time to request email app password after log in
    if(content.pass == ""){
        std::string temp = requestEmailPass();
        if(temp == "quit") return;
        temp.clear();

        content.pass = emailPass;
    }

    if(!sendEmail(content)){
        std::cout << "+ Log in failed +" << std::endl;
    }
}

void datastructures::create_contact(){
    if(!isSignIn()) return;

    Contact newContact;
    std::string input;

    // use username logic, may be update function name
    input = askUserName();
    if(input == "quit") return;
    newContact.username = input;

    input = askEmail();
    if(input == "quit") return;
    newContact.email = input;

    currentUser.contacts.push_back(newContact);
    // update database
}

Contact datastructures::get_contact(std::string contactName){
    Contact contact;
    if(!isSignIn()) return contact;

    for (auto con : currentUser.contacts){
        if(con.username == contactName){
            contact = con;
            break;
        }
    }

    return contact;
}

void datastructures::update_contact(const std::string& contactName){
    if(!isSignIn()) return;

    Contact updatedContact;
    std::string input;

    for(auto& contact : currentUser.contacts){
        if(contact.username == contactName){

            std::cout << "Do you want to update contact name?" << std::endl;
            input = askYesOrNo();
            if(input == "quit") return;
            if(input == "y"){
                input = askUserName();
                if(input == "quit") return;
                updatedContact.username = input;
            }

            std::cout << "Do you want to update contact email?" << std::endl;
            input = askYesOrNo();
            if(input == "quit") return;
            if(input == "y"){
                input = askEmail();
                if(input == "quit") return;
                updatedContact.email = input;
            }

            if(updatedContact.username != ""){
                contact.username = updatedContact.username;
            }

            if(updatedContact.email != ""){
                contact.email = updatedContact.email;
            }

            break;
        }
    }

    // update database
}

void datastructures::remove_contact(const std::string &contactName){
    if(!isSignIn()) return;

    auto& contacts = currentUser.contacts;

    for (auto contact = contacts.begin(); contact != contacts.end(); ++contact)
    {
        if (contact->username == contactName)
        {
            contacts.erase(contact);
            break;
        }
    }

    // update database
}

void datastructures::print_contacts(){
    if(!isSignIn()) return;

    for(auto contact : currentUser.contacts){
        space();
        std::cout << contact.username << std::endl;
        std::cout << contact.email << std::endl;
    }

}


// not ready
void datastructures::create_new_user(){
    User newUser;
    std::string inputLine;
    std::string pass;
    std::string email;

    std::cout << "Create new user:" << std::endl;
    std::cout << "(type 'quit' to exit creating the new user at any point)" << std::endl;
    space();

    // new user information request
    // ask username loop
    while(true){
        inputLine = askUserName();
        if(inputLine == "quit") return;
        if(usernameAlreadyExist(inputLine)) continue;

        break;
    }

    newUser.username = inputLine;

    // ask password and reask to check if they matches
    inputLine = askPassword(newUser.username);
    if(inputLine == "quit") return;
    pass = inputLine;
    inputLine = reaskPassword(pass);
    if(inputLine == "quit") return;

    // hash and salt the password and store password hash and salt
    hashSalt newHashSalt = hash_and_salt_password(pass);
    newUser.passwordHash = newHashSalt.hash;
    newUser.passwordSalt = newHashSalt.salt;

    inputLine.clear();
    pass.clear();

    // email, email app password and validation code loop
    int attemptsLeft = 5;
    while (true){
        if(attemptsLeft <= 0){
            std::cout << "+ Too many attempts! Quiting sign in with new user +" << std::endl;
            return;
        }

        std::cout << "++ attemps left: " << attemptsLeft << " ++" << std::endl;
        attemptsLeft --;

        // ask email loop
        while(true){
            inputLine = askEmail();
            if(inputLine == "quit") return;
            if(emailAlreadyExist(inputLine)) continue;

            break;
        }
        email = inputLine;

        // ask email app password
        inputLine = askEmailAppPassword(newUser.username);
        if(inputLine == "quit") return;

        pass = inputLine;
        std::cout << inputLine << std::endl;

        ReturnStatus status = emailCodeValidation(email, pass);
        if(status == QUIT){
            return;
        } else if(status == AUTHFAIL) {
            std::cout << "+ Authentication failure! Email and/or emails app password is wrong +" << std::endl;
            continue;
        } else if(status == CODEFAIL) {
            return;
        }

        pass.clear();
        break;
    }


    newUser.email = email;

    users.push_back(newUser);

    if(saveUsers(USERSFILE, users)){
        std::cout << "You have succesfully sign in! \n (type 'log_in " << newUser.username << "' if you want to log in)" << std::endl;
    }
    else {
        std::cout << "Sign in has failed! \n (type 'sign_in' if you want to try again)" << std::endl;
    }

}


void datastructures::load_existing_user(std::string usernameOrEmail)
{
    bool isEmail;
    std::string line;
    std::string pass;
    User userTemp;

    remove_current_user();

    // check if username or email exist
    if (validEmail(usernameOrEmail)){
        isEmail = true;
    } else if (validateUserName(usernameOrEmail)){
        isEmail = false;
    } else {
        std::cout << "\nNot valid username or email. Please try again type 'log_in <valid username or email>'\n";
        return;
    }

    std::cout << "Please Log in " << usernameOrEmail << " by providing password\n";

    while(true){
        std::cout << "Password: ";
        line = passInput();

        if(line == "quit")return;

        if(!checkPassLength(line)){
            std::cout << "Too long or too short password!" << std::endl;
        } else {
            pass = line;
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
            std::cout << " log in has failed! wrong username or password" << std::endl;
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
            std::cout << " log in has failed! wrong username or password" << std::endl;
            return;
        }
    }

    /*
    if(isEmail){
        if(userTemp.email != usernameOrEmail){
            std::cout << " log in has failed! wrong username or password" << std::endl;
            return;
        }
    } else {
        if(userTemp.username != usernameOrEmail){
            std::cout << " log in has failed! wrong username or password" << std::endl;
            return;
        }
    }
    */

    hashSalt userHashSalt = {userTemp.passwordHash, userTemp.passwordSalt};

    if(authenticate(pass, userHashSalt)){
        set_current_user(userTemp);
        pageHeader("WELCOME TO THE MAIL SYSTEM", get_current_user().username);
    } else {
        std::cout << " log in has failed! wrong username or password" << std::endl;
    }
}

User datastructures::get_current_user(){
    return currentUser;
}

void datastructures::set_current_user(User user){
    currentUser = user;
}

void datastructures::print_email_by_id(){

}

void datastructures::delete_email_by_id(){

}

void datastructures::remove_current_user()
{
    User user;
    currentUser = user;
    emailPass.clear();
    pageHeader("WELCOME TO THE MAIL SYSTEM", get_current_user().username);
}

std::string datastructures::requestEmailPass(){
    std::string input = askEmailAppPassword(currentUser.username);
    if(input == "quit") return input;

    emailPass = input;
    return input;
}

bool datastructures::usernameAlreadyExist(const std::string& username){

    for (User& user : users) {
        if (user.username == username){
            std::cout << "+ Username not accepted. Username already in use. +" << std::endl;
            return true;
        }
    }

    return false;
}

bool datastructures::emailAlreadyExist(const std::string& email){
    for (User& user : users) {
        if (user.email == email){
            std::cout << "+ Email not accepted. Email already in use. +" << std::endl;
            return true;
        }
    }

    return false;
}

bool datastructures::isSignIn(){
    if(currentUser.username == ""){
        std::cout << "+ User is not log in. +\n+ Log in by 'log_in <username or email>' +\n+ or sign in by 'sign_in' +" << std::endl;
        return false;
    }
    return true;
}

std::vector<std::string> datastructures::split (const std::string& line, const char& separator){
    std::string newLine = line;
    std::vector<std::string> parts;
    size_t position = 0;
    std::string part;
    while((position = newLine.find(separator)) != std::string::npos){
        part = newLine.substr(0, position);
        parts.push_back(part);
        newLine.erase(0, position + 1);
    }
    parts.push_back(newLine);
    return parts;
}

std::vector<std::string> datastructures::split (const std::string& line, const char& separator, bool ignorWhiteSpace){

    if(ignorWhiteSpace != true){
        std::vector< std::string > parts = split(line, separator);
        return parts;
    } else {

        std::string newLine = line;
        std::vector<std::string> parts;
        size_t position = 0;
        std::string part;
        while((position = newLine.find(separator)) != std::string::npos){
            part = newLine.substr(0, position);
            if(part != ""){
                parts.push_back(part);
            }
            newLine.erase(0, position + 1);
        }
        parts.push_back(newLine);
        return parts;
    }
}
