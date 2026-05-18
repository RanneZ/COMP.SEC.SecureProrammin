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

    // EMAIL //

    // starts guided email creation.
    // Recipient(s): accepts emails or already existing contact name
    // Subject: subject text
    // Message: message text
    // shows all the valid and invalid emails
    // Ask if user want to send email
    // if app password is empty then ask
    // Emails App Password:
    // if successful it will sore app password
    // in variable until app is close or user is log out
    // if not tell auth has failed
    void createEmail();

    // CONTACT //

    // starts guided contact creation.
    // ask for contact name
    // and then contact email address
    void createContact();

    // gets contact if founded
    Contact getContact(std::string contactName);

    // starts guided contact update form.
    // ask if user want to update name
    // if yes ask new name
    // ask if user want to update email
    // if yes ask email
    // save changes
    void updateContact(const std::string& contactName);

    // if conatct is found from contact list with name
    // remove it from contact and save changes
    void removeContact(const std::string& contactName);

    // print all the contact names ans emails
    void printJustContacts();

    // USER //

    // start
    // starts guided user creation.
    // Username: accepts unique username
    // Password: accepts password that is not
    // in 10 000 dangerous list and dosent contain username
    // and is atleast 8-64 charracter long
    // Confirm password: accepts password if it match with previous password
    // Email: accepts email address
    // Email App Password: acceps password
    // if email auth faill ask Email and Emali App Password again 4 more times
    // until exits user creation
    // if auth is successfull send to that email 6 digit validation code
    // Validation code: accepts 6 number code and can try up to 5 times
    // until exits user creation
    // if success create new user and save it
    void createNewUser();

    // if given existing username or email
    // password: accepts password and hash it and compare it to user own passwordHash
    // in success log in the user
    void logInUser(std::string usernameOrEmail);

    // request new password:
    // Confirm password:
    // if app password is empty then ask
    // Emails App Password:
    // if auth is successfull send to that email 6 digit validation code
    // Validation code: accepts 6 number code and can try up to 5 times
    // until exits change password
    // if success updates password and save changes
    void changePassword();

    // request new email:
    // if app password is empty then ask
    // Emails App Password:
    // if auth for old email is successfull send to that email 6 digit validation code
    // Validation code: accepts 6 number code and can try up to 5 times
    // until exits change email address
    // if success ask new emails Email App Password:
    // if auth for new email is successfull send to that email 6 digit validation code
    // Validation code: accepts 6 number code and can try up to 5 times
    // until exits change email address
    // if success updates email and save changes
    void changeEmailAddress();

    void logOutUser();

    void printUserInfo();

    // GETTER //
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
