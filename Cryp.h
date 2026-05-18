#ifndef CRYP_H
#define CRYP_H

#include <string>

struct hashSalt{
    std::string hash;
    std::string salt;
};

// hash and salt the password and then return hash and salted password
hashSalt hashAndSaltPassword(std::string password);

// hash the input password and compare it to the users
// stored hashed password
// return true if both hashs match to each other
bool authenticate(std::string inputPassword, hashSalt hashAndSalt);

// generate secure 6 digit number
std::string random6NumberCode();

// hash a string and retuns it (not used to store)
// it is used only to compare with dangerous password
// that are hash also
std::string hashString(std::string string);

#endif // CRYP_H
