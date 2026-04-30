#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

bool validateUserName(const std::string& username);
bool validEmail(const std::string& email);
bool checkPassLength(const std::string& password);

#endif // VALIDATION_H
