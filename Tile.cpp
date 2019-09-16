
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape) {}

Colour Tile::getColour() { return colour; }

Shape Tile::getShape() { return shape; }

bool Tile::equals(Tile* tile) {
  return colour == tile->getColour() && shape == tile->getShape();
}