// https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2505.htm
// this did get me to try to make something that can securly remove password from memory

#ifndef SECURECLEAR_H
#define SECURECLEAR_H

#include <string>

// securly overwrite the string and then relese it
void stringSecureClear(std::string& string);

#endif // SECURECLEAR_H
