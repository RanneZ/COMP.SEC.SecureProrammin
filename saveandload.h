#ifndef SAVEANDLOAD_H
#define SAVEANDLOAD_H
#include <string>
#include "datastructures.h"

bool saveUser(const std::string& fileName, User& user);
User loadUser(const std::string& fileName, std::string& username);

#endif // SAVEANDLOAD_H
