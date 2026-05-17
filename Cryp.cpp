#include "Cryp.h"

#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

hashSalt hashAndSaltPassword(std::string password){

    // generate salt
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::byte saltBytes[16];
    rng.GenerateBlock(saltBytes, sizeof(saltBytes));

    // salting
    std::string salt;
    CryptoPP::StringSource(saltBytes, sizeof(saltBytes), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(salt)));
    std::string passSalt = password+salt;

    // hashing
    std::string hash;
    CryptoPP::SHA256 sha;
    CryptoPP::StringSource(passSalt, true, new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));

    hashSalt hashResult;
    hashResult.hash = hash;
    hashResult.salt = salt;

    return hashResult;
}

bool authenticate(std::string inputPassword, hashSalt hashAndSalt){

    // salting and hashing the input
    std::string inputHash;
    std::string inputPassSalt = inputPassword + hashAndSalt.salt;
    CryptoPP::SHA256 sha;
    CryptoPP::StringSource(inputPassSalt, true, new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(new CryptoPP::StringSink(inputHash))));

    // check if passwords macth
    if(hashAndSalt.hash == inputHash){
        return true;
    } else {
        return false;
    }
}

std::string random6NumberCode(){
    // generate random data
    CryptoPP::AutoSeededRandomPool rng;
    std::string code = "";

    for(int i = 0; i < 6; ++i) {
        CryptoPP::byte digit;
        // Haetaan satunnainen tavu ja skaalataan se välille 0-9
        rng.GenerateBlock(&digit, 1);
        code += std::to_string(digit % 10);
    }

    return code;
}

std::string hashString(std::string string){
    // hashing the string
    std::string hash;
    CryptoPP::SHA256 sha;
    CryptoPP::StringSource(string, true, new CryptoPP::HashFilter(sha, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));

    return hash;
}
