#ifndef CRYP_H
#define CRYP_H
#include <string>

struct hashSalt{
    std::string hash;
    std::string salt;
};

hashSalt hash_and_salt_password(std::string password);
bool authenticate(std::string inputPassword, hashSalt hashAndSalt);
std::string random6NumberCode();
std::string hashString(std::string string);

#endif // CRYP_H
