
#ifndef ASSIGN2_HELPER_H
#define ASSIGN2_HELPER_H

#include "Tile.h"

class Helper {
 public:
  bool fileExists(std::string filename);
  bool isValidTile(Colour colour, Shape shape);
};

#endif  // ASSIGN2_HELPER_H
