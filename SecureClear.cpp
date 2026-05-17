// https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2505.htm
// this did get me to try to make something that can securly remove password from memory

#include "SecureClear.h"

void stringSecureClear(std::string& string){
    // points first memory location of string
    // volatile forces compiler to not optimaze it
    volatile char* pChar = const_cast<volatile char*>(string.data());

    for(size_t i = 0; i < string.size(); ++i){
        pChar[i] = 0;
    }
    string.clear();
}
