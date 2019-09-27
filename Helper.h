
#ifndef ASSIGN2_HELPER_H
#define ASSIGN2_HELPER_H

#include "Tile.h"
namespace Help
{

class Helper
{
public:
  Helper();
  bool isValidFormat(std::string filename);
  bool isValidTile(Colour colour, Shape shape);
  bool isASCII(std::string n);
  bool isNumber(std::string h);
};

} // namespace helperspace

#endif // ASSIGN2_HELPER_H
