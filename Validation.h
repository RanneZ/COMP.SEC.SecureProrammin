#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

enum ReturnStatus {
    AUTHFAIL,
    CODEFAIL,
    QUIT,
    SUCCESS
};

bool validateUserName(const std::string& username);
bool validEmail(const std::string& email);
bool validateSubject(const std::string& subject);
bool validateMessage(const std::string& message);

bool validate6DigitCode(const std::string& code);
bool checkPassLength(const std::string& password);
bool checkPassList(std::string password);
bool checkPassSubString(const std::string& password, const std::string& username);
bool checkPass(const std::string& password, const std::string& username);
ReturnStatus emailCodeValidation(const std::string& emailAddres, const std::string& emailPass);
bool checkPasswordsMatches(const std::string& password, const std::string& repassword);


#endif // VALIDATION_H
