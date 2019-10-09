
#ifndef ASSIGN2_HELPER_H
#define ASSIGN2_HELPER_H

#include <string>

namespace Helper {
// file and input validation methods
bool isValidFormat(std::string filename);
bool isASCII(std::string n);
bool isNumber(std::string h);
bool fileExists(std::string fileName);
}  // namespace Helper

#endif  // ASSIGN2_HELPER_H
