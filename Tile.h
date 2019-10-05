
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

// #include <memory>
#include <string>
#include "TileCodes.h"

class Tile {
  Colour colour;
  Shape shape;
  // std::shared_ptr<bool> tile;

 public:
  Tile();
  Tile(Colour colour, Shape shape);
  Tile(const Tile& toCopy);
  // void setTile(bool isSet);
  Colour getColour();
  Shape getShape();
  bool equals(Tile tile);
  std::string toString();
};

#endif  // ASSIGN2_TILE_H
