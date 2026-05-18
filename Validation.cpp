#include "Validation.h"
#include "DangerousPasswords.h"
#include "Cryp.h"
#include "Email.h"
#include "Config.h"

#include <unordered_set>
#include <iostream>
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

bool validateSubject(const std::string& subject){
    std::regex pattern(R"(^[^\x00-\x1F\x7F\r\n]{1,200}$)");
    if(!std::regex_match(subject, pattern)) return false;

    return true;
}

bool validateMessage(const std::string& message){
    // make sure message is not too long and dosent contain \0 symboles
    if(message.size() > 10000) return false;

    return message.find('\0') == std::string::npos;
}

bool validate6DigitCode(const std::string& code){
    // make sure there is 6 number and they are all 0-9
    std::regex pattern("^[0-9]{6}");
    if(!std::regex_match(code, pattern)) return false;

    return true;
}

bool checkPassLength(const std::string& password){
    // check if password is too short or too long
    if (password.length() < 8 || password.length() > 64){
        std::cout << "WARNING: Password is less than 8 characters long or longer than 64 characters!" << std::endl;
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
        std::cout << "WARNING: Password exist in OWASP dangerous password list. this is security risk!" << std::endl;
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

ReturnStatus emailCodeValidation(const std::string& emailAddres, const std::string& emailPass){

    // crate code
    std::string code = random6NumberCode();

    std::string input;

    // add email address to 'to' (recipient)
    std::vector<std::string> to;
    to.push_back(emailAddres);

    // create email
    emailContent content;
    content.from = emailAddres;
    content.pass = emailPass;
    content.to = to;
    content.subject = "Mail system validation code";
    content.message = "Here is the validation code \n\n"+ code;

    // if email smtp auth faile return authfail
    if(!sendEmail(content)){
        return AUTHFAIL;
    }

    // lets user to try validation code for 5 times before exiting
    int attemptsLeft = 5;
    std::cout << "Check your given email inbox. There should be \nEmail that have 6 number code" << std::endl;
    std::cout << "Validation code: ";
    while (getline(std::cin, input)){
        if(input == BACK)return QUIT;

        if (!validate6DigitCode(input)){
            std::cout << "Wrong amount digits \n code is 6 digit long" << std::endl;
        } else {
            if (input != code){
                attemptsLeft = attemptsLeft - 1;
                if(attemptsLeft <= 0){
                    return CODEFAIL;
                }
                std::cout << "Invalid validation code! "<< attemptsLeft <<" attempts remaining" << std::endl;
            } else {
                break;
            }
        }
        std::cout << "Validation code: ";
    }

    return SUCCESS;
}

// you get it!
// check if two password match
bool checkPasswordsMatches(const std::string &password, const std::string &repassword){
    if (password == repassword) return true;
    std::cout << "Passwords do not match with each other!" << std::endl;
    return false;
}


