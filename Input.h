#ifndef INPUT_H
#define INPUT_H

#include <string>
std::string passInput();
std::string askUserName();
std::string askPassword(const std::string& username);
std::string reaskPassword(const std::string& password);
std::string askEmail();
std::string askEmailAppPassword(const std::string& username);
std::string askSubject();
std::string askMessage();
std::string askYesOrNo();

#endif // INPUT_H
