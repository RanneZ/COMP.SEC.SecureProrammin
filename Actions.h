#ifndef ACTIONS_H
#define ACTIONS_H

#include "Email.h"

#include <string>
#include <vector>
#include <ctime>

struct Contact {
    std::string username;
    std::string email;
};

struct User {
    std::string username;
    std::string email;
    std::string passwordHash;
    std::string passwordSalt;
    std::vector<Contact> contacts;
};

class Actions
{
public:

    Actions();
    ~Actions();

    // EMAIL
    void createEmail();

    // CONTACT
    void createContact();
    Contact getContact(std::string contactName);
    void updateContact(const std::string& contactName);
    void removeContact(const std::string& contactName);
    void printJustContacts();

    // USER
    void createNewUser();
    void logInUser(std::string usernameOrEmail);
    void changePassword();
    void changeEmailAddress();
    void logOutUser();
    void printUserInfo();

    // GETTER
    User getCurrentUser();

private:
    std::vector<User> users;
    User currentUser;
    std::string emailPass;

    void printContacts();
    void prepareEmail(emailContent& content);
    std::string requestEmailPass();
    bool usernameAlreadyExist(const std::string& username);
    bool emailAlreadyExist(const std::string& email);
    bool isLogIn();

    void updateUsers();

    void exitAction(const std::string& message);
    bool inputIsBack(std::string input);
};

#endif // ACTIONS_H
