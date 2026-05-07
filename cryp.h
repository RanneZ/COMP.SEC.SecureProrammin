#ifndef CRYP_H
#define CRYP_H
#include <vector>
#include <string>

struct hashSalt{
    std::string hash;
    std::string salt;
};

hashSalt hash_and_salt_password(std::string password);
bool authenticate(std::string inputPassword, hashSalt hashAndSalt);
std::string random6NumberCode();

#endif // CRYP_H
