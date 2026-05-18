#ifndef INPUT_H
#define INPUT_H

#include <string>

// handle inputs so that replace console shown inputs with '*'
std::string hiddenInput();

// handle username input (also contact name input)
std::string inputUsername();

// handle password inputs
// takes username also it is needet at password validation later
// retun password if validations pass (look validation.cpp & .h)
std::string inputPassword(const std::string& username);

// handle re asking password and check that passwords matches
std::string reinputPassword(const std::string& password);

// handle email address input and validates it (look validation.cpp & .h)
std::string inputEmail();

// handle email app password inputs
// takes username also it is needet at password validation later
// retun password if validations pass (look validation.cpp & .h)
std::string inputEmailAppPassword(const std::string& username);

// handle subject inputs and return it if pass validation
// (look validation.cpp & .h)
std::string inputSubject();

// handle message inputs and return it if pass validation
// (look validation.cpp & .h)
std::string inputMessage();

// quess what this do!
std::string inputYesOrNo();

#endif // INPUT_H
