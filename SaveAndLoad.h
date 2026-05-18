// This is gennerated by AI.
// ChatGPT (GPT-5.5.)

#ifndef SAVEANDLOAD_H
#define SAVEANDLOAD_H

#include "Actions.h"

#include <string>
#include <vector>

// save users to the 'database' (fansy name for txt file)
bool saveUsers(const std::string& fileName, const std::vector<User>& users);

// load users from the 'database' (fansy name for txt file) and returns it
std::vector<User> loadUsers(const std::string& fileName);


#endif // SAVEANDLOAD_H
