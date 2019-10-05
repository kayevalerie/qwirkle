
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>
#include "TileCodes.h"

class Tile {
  Colour colour;
  Shape shape;

 public:
  Tile();
  Tile(Colour colour, Shape shape);
  Tile(const Tile& toCopy);
  Colour getColour();
  Shape getShape();
  bool equals(Tile tile);
  std::string toString();
};

#endif  // ASSIGN2_TILE_H
