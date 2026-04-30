#include "saveandload.h"
#include "jsonconverter.h"
#include "datastructures.h"
#include <fstream>

bool saveUser(const std::string& fileName, User& user){
    std::ifstream file(fileName);
    nlohmann::json j;

    if(file) file >> j;
    else j = nlohmann::json::array();

    bool found = false;

    for (auto& item : j){
        User existing = item.get<User>();

        if (existing.username == user.username){
            existing = user;
            found = true;
            break;
        }
    }

    if (!found) j.push_back(user);

    std::ofstream outFile(fileName);
    if (!outFile) return false;
    outFile << j.dump(4);

    return true;
}

User loadUser(const std::string& fileName, std::string& username){
    std::ifstream file(fileName);
    User nulluser;
    if(!file) return nulluser;

    nlohmann::json j;
    file >> j;

    for (const auto& item : j){
        User user = item.get<User>();

        if(user.username == username){
            return user;
        }
    }

    return nulluser;
}
