#ifndef SPLIT_H
#define SPLIT_H

#include <string>
#include <vector>

std::vector<std::string> split (const std::string& line, const char& separator);
std::vector<std::string> split (const std::string& line, const char& separator, bool ignorWhiteSpace);

#endif // SPLIT_H
