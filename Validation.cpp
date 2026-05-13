#include "Validation.h"
#include "DangerousPasswords.h"
#include <unordered_set>
#include <iostream>
#include "Cryp.h"
#include <regex>

bool validateUserName(const std::string &username){
    std::regex pattern("^[a-zA-Z](?!.*[._]{2})[a-zA-Z0-9._]{1,18}[a-zA-Z]$");
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

bool validate6DigitCode(const std::string& code){
    std::regex pattern("^[0-9]{6}");
    if(!std::regex_match(code, pattern)) return false;

    return true;
}

bool checkPassLength(const std::string& password){
    // check if password is too short or too long
    if (password.length() < 8 || password.length() > 64){
        std::cout << "WARNING: Password is less than 8 characters long or longer than 64 characters !" << std::endl;
        return false;
    }
    return true;
}

bool checkPassList(std::string password){
    // hash the password with sha256
    std::string hashPass = hashString(password);

    // change hashpass to lowercase -> cryp hash to uppercase and my dangerous passwords are lowercase -> need to fix later
    std::transform(hashPass.begin(), hashPass.end(), hashPass.begin(),[](unsigned char c) { return std::tolower(c); });

    // check if hash password exist in dangerous password list
    const auto& dangerousList = getDangerousPasswords();
    if(dangerousList.find(hashPass) != dangerousList.end()){
        std::cout << "WARNING: Password exist in OWASP dangerous password list!" << std::endl;
        return false;
    }
    return true;
}

bool checkPassSubString(const std::string& password, const std::string& username){
    // check if username is includet in password
    if (password.find(username) != std::string::npos) {
        std::cout << "WARNING: Password contains username. this is security risk!" << std::endl;
        return false;
    }
    return true;
}

bool checkPass(const std::string& password, const std::string& username){
    // normalize password and change it to lowercase
    std::string normalizedPass = password;
    std::transform(normalizedPass.begin(), normalizedPass.end(), normalizedPass.begin(),[](unsigned char c) { return std::tolower(c); });

    // normalize username and change it to lowercase
    std::string normalizedUser = username;
    std::transform(normalizedUser.begin(), normalizedUser.end(), normalizedUser.begin(),[](unsigned char c) { return std::tolower(c); });

    // check if password is too short or too long
    if(!checkPassLength(password)){
        return false;
    }

    // check if username is includet in password
    if(!checkPassSubString(normalizedPass, normalizedUser)){
        return false;
    }

    // check if hash password exist in OWASP dangerous password list
    if(!checkPassList(normalizedPass)){
        return false;
    }

    return true;

}

bool emailCodeValidation(const std::string& emailAddres, const std::string& emailPass){

    std::string code = random6NumberCode();
    std::string line;

    // create email
    emailContent content;
    content.from = emailAddres;
    content.pass = emailPass;
    content.to = emailAddres;
    content.subject = "Mail system validation code";
    content.message = "Here is the validation code \n\n"+ code;

    if(!sendEmail(content)){
        // comment
        return false;
    }

    int attemptsLeft = 5;
    std::cout << "Check your given email inbox. There should be \nEmail that have 6 number code" << std::endl;
    std::cout << "Validation code: ";
    while (getline(std::cin, line)){
        if(line == "quit")return false;

        if (!validate6DigitCode(line)){
            std::cout << "Wrong amount digits \n code is 6 digit long" << std::endl;
        } else {
            if (line != code){
                attemptsLeft = attemptsLeft - 1;
                if(attemptsLeft <= 0){
                    std::cout << "Too many attempts! exiting Sign in" << std::endl;
                    return false;
                }
                std::cout << "Invalid validation code! "<< attemptsLeft <<" attempts remaining" << std::endl;
            } else {
                break;
            }
        }
        std::cout << "Validation code: ";
    }

    return true;
}

bool checkPasswordsMatches(const std::string &password, const std::string &repassword){
    if (password == repassword) return true;
    std::cout << "Confirm password do not match with password!" << std::endl;
    return false;
}

bool checkUsernameDosentExist(const std::string &username){

}

bool checkEmailAddresDosentExist(const std::string &emailAddres){

}
