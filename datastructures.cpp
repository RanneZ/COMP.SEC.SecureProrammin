#include "datastructures.h"
#include "saveandload.h"
#include <iostream>
#include "ui.h"
#include "validation.h"
#include "input.h"
#include "cryp.h"
#include "Config.h"


datastructures::datastructures(email email) {
    emailHandler = email;
}

datastructures::~datastructures(){

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
    std::string line;
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
    std::cout << "Username: ";

    while (getline(std::cin, line)){
        if(line == "quit")return;

        if (!validateUserName(line)){
            std::cout << "Invalid username (containe one or more unalowed charater)" << std::endl;
        } else {
            break;
        }
        std::cout << "Username: ";
    }

     newUser.username = line;

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

    while(true){
        std::cout << "Confirm Password: ";
        line = passInput();

        if(line == "quit")return;

        if(line != pass){
            std::cout << "Confirm password do not match with password!" << std::endl;
        } else {
            break;
        }
    }

    hashSalt newHashSalt = hash_and_salt_password(pass);
    pass = "";
    newUser.passwordHash = newHashSalt.hash;
    newUser.passwordSalt = newHashSalt.salt;

    std::cout << "Email: ";
    while (getline(std::cin, line)){
        if(line == "quit")return;

        if (!validEmail(line)){
            std::cout << "Invalid email address!" << std::endl;
        } else {
            break;
        }
        std::cout << "Email: ";
    }

    std::string email = line;

    while(true){
        std::cout << "Emails App Password: ";
        line = passInput();

        if(line == "quit")return;

        if(!checkPassLength(line)){
            std::cout << "Too long or too short password!" << std::endl;
        } else {
            pass = line;
            break;
        }
    }

    // hash and salt the email app password
    newHashSalt = hash_and_salt_password(pass);
    //pass = "";
    newUser.emailPassHash = newHashSalt.hash;
    newUser.emailPassSalt = newHashSalt.salt;

    // +
    // check that Email is not in use
    // send email to the email addres that have validation code
    // +


    std::string subject = "Mail system validation code";
    std::string code = random6NumberCode();
    std::string message = "Here is the validation code \n\n"+ code;

    emailHandler.sendEmail(email,
                           pass,
                           email,
                           subject,
                           message);
    pass = "";


    int attemptsLeft = 5;
    std::cout << "Check your given email inbox. There should be \nEmail that have 6 number code" << std::endl;
    std::cout << "Validation code: ";
    while (getline(std::cin, line)){
        if(line == "quit")return;

        if (line != code){
            attemptsLeft = attemptsLeft - 1;
            if(attemptsLeft <= 0){
                std::cout << "Too many attempts! exiting Sign in" << std::endl;
                return;
            }
            std::cout << "Invalid validation code! "<< attemptsLeft <<" attempts remaining" << std::endl;
        } else {
            break;
        }
        std::cout << "Validation code: ";
    }

    newUser.email = email;


    if(saveUser(USERSFILE, newUser)){
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

    if (validEmail(usernameOrEmail)){
        isEmail = true;
    }
    else if (validateUserName(usernameOrEmail)){
        isEmail = false;
    }
    else {
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

    User user = loadUser(USERSFILE, usernameOrEmail);
    if(user.username == ""){
        std::cout << " log in has failed! wrong username or password" << std::endl;
        return;
    }

    hashSalt userHashSalt = {user.passwordHash, user.passwordSalt};

    if(authenticate(pass, userHashSalt)){
        set_current_user(user);
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
