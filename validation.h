#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

bool validateUserName(const std::string& username);
bool validEmail(const std::string& email);

bool checkPassLength(const std::string& password);
bool checkPassList(std::string password);
bool checkPassSubString(const std::string& password, const std::string& username);
bool checkPass(const std::string& password, const std::string& username);

#endif // VALIDATION_H
