#ifndef SPLIT_H
#define SPLIT_H

#include <string>
#include <vector>

// split string from all the point of that separator and return all the parts
std::vector<std::string> split (const std::string& line, const char& separator);
std::vector<std::string> split (const std::string& line, const char& separator, bool ignorWhiteSpace);


#endif // SPLIT_H
