#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
#include "Email.h"

bool validateUserName(const std::string& username);
bool validEmail(const std::string& email);

bool validate6DigitCode(const std::string& code);
bool checkPassLength(const std::string& password);
bool checkPassList(std::string password);
bool checkPassSubString(const std::string& password, const std::string& username);
bool checkPass(const std::string& password, const std::string& username);
bool emailCodeValidation(const std::string& emailAddres, const std::string& emailPass);
bool checkPasswordsMatches(const std::string& password, const std::string& repassword);
bool checkUsernameDosentExist(const std::string& username);
bool checkEmailAddresDosentExist(const std::string& emailAddres);

#endif // VALIDATION_H
