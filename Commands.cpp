#include "Commands.h"
#include <iostream>

std::vector<Cmd> create_cmds(datastructures& data) {

    static std::string emailidx = "([a-zA-Z0-9-]+)";
    static std::string usernamex = "([a-zA-Z](?!.*[._]{2})[a-zA-Z0-9._]{1,18}[a-zA-Z])";
    static std::string userEmailx = "([a-zA-Z0-9._-]+@(?:[a-z0-9]+(?:-[a-z0-9]+)*\\.)+[a-z]{2,})";
    //std::string coordx = "\\(([0-9]+),([0-9]+)\\)";
    //std::string numx = "([0-9]+)";
    static std::string ws = "\\s+";

    return{
        {
            "read_email",
            std::regex("^read_email" + ws + emailidx + "$"),
            [](const std::smatch& match) {
                std::cout << "Read email for ID: " << match[1] << std::endl;
                // run function here
            }
        },
        {
            "send_email",
            std::regex("^send_email"),
            [](const std::smatch& match){
                std::cout << "Send message!" << std::endl;
                // run function here
            }
        },
        {
            "delete_email",
            std::regex("^delete_email" + ws + emailidx + "$"),
            [](const std::smatch& match) {
                std::cout << "Delete email for ID: " << match[1] << std::endl;
                // run function here
            }
        },
        {
            "inbox_view",
            std::regex("^inbox_view"),
            [](const std::smatch& match){
                std::cout << "Inbox" << std::endl;
                // run function here
            }
        },
        {
            "send_folder_view",
            std::regex("^send_folder_view"),
            [](const std::smatch& match){
                std::cout << "Send_folder" << std::endl;
                // run function here
            }
        },
        {
            "log_in",
            std::regex("^log_in"+ ws + usernamex + "$" ),
            [&](const std::smatch& match){
                std::cout << "Log in user: " << match[1] << std::endl;
                data.load_existing_user(match[1]);
            }
        },
        {
            "log_in",
            std::regex("^log_in"+ ws + userEmailx + "$" ),
            [&](const std::smatch& match){
                std::cout << "Log in user: " << match[1] << std::endl;
                data.load_existing_user(match[1]);
            }
        },
        {
            "sign_in",
            std::regex("^sign_in"),
            [&](const std::smatch& match){
                std::cout << "Sign in new user." << std::endl;
                data.create_new_user();
            }
        },
        {
            "log_out",
            std::regex("^log_out"),
            [&](const std::smatch& match){
                std::cout << "Log out user: " << match[1] << std::endl;
                data.remove_current_user();
            }
        }
    };
};
