
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape) {}

Tile::Tile(Tile& toCopy) : colour(toCopy.getColour), shape(toCopy.getColour) {}

Colour Tile::getColour() { return colour; }

Shape Tile::getShape() { return shape; }

bool Tile::equals(Tile *tile) {
  return colour == tile->getColour() && shape == tile->getShape();
}

std::string Tile::toString() { return colour + std::to_string(shape); }
