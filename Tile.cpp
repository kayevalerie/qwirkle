
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape) {}

Colour Tile::getColour() { return colour; }

Shape Tile::getShape() { return shape; }

bool equals(Tile* tile) {}