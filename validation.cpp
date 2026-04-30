#include "validation.h"
#include <regex>

bool validateUserName(const std::string &username){
    std::regex pattern("^[a-zA-Z](?!.*[._]{2})[a-zA-Z0-9._]{1,18}[a-zA-Z]");
    if(!std::regex_match(username, pattern)) return false;

    return true;
}

bool validEmail(const std::string& email){
    // OWASP Input Validation/Email Address Validation
    // https://cheatsheetseries.owasp.org/cheatsheets/Input_Validation_Cheat_Sheet.html#email-address-validation

    size_t atPosition = email.find('@');
    if (atPosition == std::string::npos) return false;

    std::string local = email.substr(0, atPosition);
    std::string domain = email.substr(atPosition + 1);

    if(local.length() > 63 || email.length() > 254) return false;

    std::regex localPattern("^[a-zA-Z0-9._-]+$");
    std::regex domainPattern("^([a-z0-9]+(-[a-z0-9]+)*\\.)+[a-z]{2,}$");

    if(!regex_match(local, localPattern)) return false;
    if(!regex_match(domain, domainPattern)) return false;

    return true;
}

bool checkPassLength(const std::string& password){
    if (password.length() < 8 || password.length() > 64) return false;
    return true;
}
