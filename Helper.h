
#ifndef ASSIGN2_HELPER_H
#define ASSIGN2_HELPER_H

#include <string>

namespace Helper {
bool isValidFormat(std::string filename);
// bool isValidTile(Colour colour, Shape shape);
bool isASCII(std::string n);
bool isNumber(std::string h);
bool fileExist(std::string fileName);
}  // namespace Helper

#endif  // ASSIGN2_HELPER_H
