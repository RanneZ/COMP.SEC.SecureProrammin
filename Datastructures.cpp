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

Message datastructures::create_email(){
    Message message;
    return message;
}

void datastructures::create_contact(){

}

Contact datastructures::get_contact(std::string contactName){
    Contact contact;
    return contact;
}


// not ready
void datastructures::create_new_user(){
    User newUser;
    std::string inputLine;
    std::string pass;

    std::cout << "Create new user:" << std::endl;
    std::cout << "(type 'quit' to exit creating the new user at any point)" << std::endl;
    std::cout << "Allowed charaters are: " << std::endl;
    std::cout << "  - a-z (upercase and lowercase)" << std::endl;
    std::cout << "  - 0-9" << std::endl;
    std::cout << "  - ._" << std::endl;
    space();
    std::cout << "User name must start with letter and can not have two or more '.' or '_' row" << std::endl;
    space();

    // ask username
    inputLine = askUserName();
    if(inputLine == "quit") return;

    newUser.username = inputLine;

    // ask password
    inputLine = askPassword(newUser.username);
    if(inputLine == "quit") return;
    pass = inputLine;

    // ask password again and check it matches with previous
    inputLine = reaskPassword(pass);
    if(inputLine == "quit") return;

    // hash and salt the password and store password hash and salt
    hashSalt newHashSalt = hash_and_salt_password(pass);
    pass = "";
    newUser.passwordHash = newHashSalt.hash;
    newUser.passwordSalt = newHashSalt.salt;

    std::cout << "Email: ";
    while (getline(std::cin, inputLine)){
        if(inputLine == "quit")return;

        if (!validEmail(inputLine)){
            std::cout << "Invalid email address!" << std::endl;
        } else {
            break;
        }
        std::cout << "Email: ";
    }

    std::string email = inputLine;

    while(true){
        std::cout << "Emails App Password: ";
        inputLine = passInput();

        if(inputLine == "quit")return;

        if(!checkPass(inputLine, newUser.username)){
        } else {
            pass = inputLine;
            break;
        }
    }

    // hash and salt the email app password
    newHashSalt = hash_and_salt_password(pass);
    newUser.emailPassHash = newHashSalt.hash;
    newUser.emailPassSalt = newHashSalt.salt;

    if(!emailCodeValidation(email, pass)) return;
    pass = "";

    newUser.email = email;

    users.push_back(newUser);

    if(saveUsers(USERSFILE, users)){
        std::cout << " you have succesfully sign in! \n (type 'log_in " << newUser.username << "' if you want to log in)" << std::endl;
    }
    else {
        std::cout << " sign in has failed! \n (type 'sign_in' if you want to try again)" << std::endl;
    }

}

// tee
void datastructures::load_existing_user(std::string usernameOrEmail)
{
    bool isEmail;
    std::string line;
    std::string pass;
    User userTemp;

    remove_current_user();

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
    } else {
        for (User& user : users) {
            if (user.username == usernameOrEmail){
                userTemp = user;
                break;
            }
        }
    }

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

    /*
    User user = loadUser(USERSFILE, usernameOrEmail, isEmail);
    if(user.username == ""){
        std::cout << " log in has failed! wrong username or password" << std::endl;
        return;
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

void datastructures::send_email(){

}

void datastructures::print_email_by_id(){

}

void datastructures::delete_email_by_id(){

}

void datastructures::remove_current_user()
{
    User user;
    currentUser = user;
    pageHeader("WELCOME TO THE MAIL SYSTEM", get_current_user().username);
}
