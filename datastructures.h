#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <string>
#include <vector>
#include <ctime>
#include "email.h"

struct Message {
    std::string sender;
    std::vector<std::string> recipients;
    std::string subject;
    std::string body;
    std::time_t timestamp;
};

struct Contact {
    std::string username;
    std::string email;
};

struct User {
    std::string username;
    std::string email;
    std::string emailPassHash;
    std::string emailPassSalt;
    std::string passwordHash;
    std::string passwordSalt;

    std::vector<Message> inbox;
    std::vector<Message> sent;
    std::vector<Contact> contacts;
};


class datastructures
{
public:

    datastructures(email email);
    ~datastructures();
    Message create_email();
    void create_contact();
    Contact get_contact(std::string contactName);
    void create_new_user();
    void load_existing_user(std::string usernameOrEmail);
    User get_current_user();
    void set_current_user(User user);
    void send_email();
    void print_email_by_id();
    void delete_email_by_id();
    void remove_current_user();

private:
    User currentUser;
    email emailHandler;

};

#endif // DATASTRUCTURES_H
