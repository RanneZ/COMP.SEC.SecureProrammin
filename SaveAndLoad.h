#ifndef SAVEANDLOAD_H
#define SAVEANDLOAD_H
#include <string>
#include <vector>
#include "Datastructures.h"

bool saveUser(const std::string& fileName, User& user);
User loadUser(const std::string& fileName, std::string& username, bool isEmail);
User loadUserByUsername(const std::string& fileName, std::string& username);
User loadUserByEmail(const std::string& fileName, std::string& emailAddres);

bool saveUsers(const std::string& fileName, const std::vector<User>& users);
std::vector<User> loadUsers(const std::string& fileName);


#endif // SAVEANDLOAD_H
