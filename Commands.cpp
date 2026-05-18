#include "Commands.h"

#include <iostream>

std::vector<Cmd> createCmds(Actions& actions) {

    static std::string emailidx = "([a-zA-Z0-9-]+)";
    static std::string usernamex = "([a-zA-Z](?!.*[._]{2})[a-zA-Z0-9._]{1,18}[a-zA-Z])";
    static std::string userEmailx = "([a-zA-Z0-9._-]+@(?:[a-z0-9]+(?:-[a-z0-9]+)*\\.)+[a-z]{2,})";
    static std::string ws = "\\s+";

    return{
        {
            "send_email",
            std::regex("^send_email$"),
            [&](const std::smatch&){
                std::cout << "Create and send email." << std::endl;
                actions.createEmail();
            }
        },
        {
            "log_in",
            std::regex("^log_in"+ ws + usernamex + "$" ),
            [&](const std::smatch& match){
                std::cout << "Log in user: " << match[1] << std::endl;
                actions.logInUser(match[1]);
            }
        },
        {
            "log_in",
            std::regex("^log_in"+ ws + userEmailx + "$" ),
            [&](const std::smatch& match){
                std::cout << "Log in user: " << match[1] << std::endl;
                actions.logInUser(match[1]);
            }
        },
        {
            "log_in",
            std::regex("^sign_in$"),
            [&](const std::smatch&){
                std::cout << "Sign in new user" << std::endl;
                actions.createNewUser();
            }
        },
        {
            "log_out",
            std::regex("^log_out$"),
            [&](const std::smatch&){
                std::cout << "Log out user" << std::endl;
                actions.logOutUser();
            }
        },
        {
            "create_contact",
            std::regex("^create_contact$"),
            [&](const std::smatch&){
                std::cout << "Create new contact." << std::endl;
                actions.createContact();
            }
        },
        {
            "print_contacts",
            std::regex("^print_contacts$"),
            [&](const std::smatch&){
                std::cout << "Print all contacts." << std::endl;
                actions.printJustContacts();
            }
        },
        {
            "print_user",
            std::regex("^print_user$"),
            [&](const std::smatch&){
                std::cout << "print user info." << std::endl;
                actions.printUserInfo();
            }
        },
        {
            "update_contact",
            std::regex("^update_contact"+ ws + usernamex + "$"),
            [&](const std::smatch& match){
                std::cout << "Update contact: " << match[1] << std::endl;
                actions.updateContact(match[1]);
            }
        },
        {
            "remove_contact",
            std::regex("^remove_contact"+ ws + usernamex + "$"),
            [&](const std::smatch& match){
                std::cout << "Remove contact from cantacts: " << match[1] << std::endl;
                actions.removeContact(match[1]);
            }
        },
        {
            "change_password",
            std::regex("^change_password$"),
            [&](const std::smatch&){
                std::cout << "Change users password." << std::endl;
                actions.changePassword();
            }
        },
        {
            "change_email_address",
            std::regex("^change_email_address$"),
            [&](const std::smatch&){
                std::cout << "Change users email address." << std::endl;
                actions.changeEmailAddress();
            }
        },
        {
            "help",
            std::regex("^help$"),
            [&](const std::smatch&){
                std::cout << "All allowed commands:" << std::endl;
                std::cout << "help" << std::endl;
                std::cout << "log_in <email>" << std::endl;
                std::cout << "log_in <username>" << std::endl;
                std::cout << "sign_in" << std::endl << std::endl;
                std::cout << "If log in. also allowe thease commands:" << std::endl;
                std::cout << "send_email" << std::endl;
                std::cout << "log_out" << std::endl;
                std::cout << "create_contact" << std::endl;
                std::cout << "print_contacts" << std::endl;
                std::cout << "print_user" << std::endl;
                std::cout << "update_contact <contact name>" << std::endl;
                std::cout << "remove_contact <contact name>" << std::endl;
                std::cout << "change_password" << std::endl;
                std::cout << "change_email_address" << std::endl;
            }
        }
    };
};
