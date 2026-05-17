#ifndef INPUT_H
#define INPUT_H

#include <string>

std::string hiddenInput();
std::string inputUsername();
std::string inputPassword(const std::string& username);
std::string reinputPassword(const std::string& password);
std::string inputEmail();
std::string inputEmailAppPassword(const std::string& username);
std::string inputSubject();
std::string inputMessage();
std::string inputYesOrNo();

#endif // INPUT_H
