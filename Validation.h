#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

enum ReturnStatus {
    AUTHFAIL,
    CODEFAIL,
    QUIT,
    SUCCESS
};

// validate username input
bool validateUserName(const std::string& username);

// validates email input
bool validEmail(const std::string& email);

// validates subject input
bool validateSubject(const std::string& subject);

// validates message input
bool validateMessage(const std::string& message);

// validates 6 digit code input
bool validate6DigitCode(const std::string& code);

// validates password length
bool checkPassLength(const std::string& password);

// validates password is not in the dangerous password list
bool checkPassList(std::string password);

// validates password that it dosent contein users username
bool checkPassSubString(const std::string& password, const std::string& username);

// validates that password has pass all the validations
bool checkPass(const std::string& password, const std::string& username);

// handle sending the email that has the validation code and
// handle validation logic
ReturnStatus emailCodeValidation(const std::string& emailAddres, const std::string& emailPass);
bool checkPasswordsMatches(const std::string& password, const std::string& repassword);


#endif // VALIDATION_H
