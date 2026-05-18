#include "Split.h"

std::vector<std::string> split(const std::string &line, const char &separator){

    std::string newLine = line;
    std::vector<std::string> parts;
    size_t position = 0;
    std::string part;

    while((position = newLine.find(separator)) != std::string::npos){
        part = newLine.substr(0, position);
        parts.push_back(part);
        newLine.erase(0, position + 1);
    }
    parts.push_back(newLine);
    return parts;
}

std::vector<std::string> split(const std::string &line, const char &separator, bool ignorWhiteSpace){

    if(ignorWhiteSpace != true){
        std::vector< std::string > parts = split(line, separator);
        return parts;
    } else {

        std::string newLine = line;
        std::vector<std::string> parts;
        size_t position = 0;
        std::string part;

        while((position = newLine.find(separator)) != std::string::npos){
            part = newLine.substr(0, position);
            if(part != ""){
                parts.push_back(part);
            }
            newLine.erase(0, position + 1);
        }
        parts.push_back(newLine);
        return parts;
    }
}
