
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape) {}

Tile::Tile(Tile& toCopy)
    : colour(toCopy.getColour()), shape(toCopy.getShape()) {}

Colour Tile::getColour() { return colour; }

Shape Tile::getShape() { return shape; }

bool Tile::equals(Tile* tile) {
  return colour == tile->getColour() && shape == tile->getShape();
}

std::string Tile::toString() {
  std::string result;

  if (colour == 'R') {
    std::string colour = "\033[0;31mR";
    result = colour + std::to_string(shape);
  } else if (colour == 'O') {
    std::string colour = "\033[0;37mO";
    result = colour + std::to_string(shape);
  } else if (colour == 'Y') {
    std::string colour = "\033[0;33mY";
    result = colour + std::to_string(shape);
  } else if (colour == 'G') {
    std::string colour = "\033[0;32mG";
    result = colour + std::to_string(shape);
  } else if (colour == 'P') {
    std::string colour = "\033[0;35mP";
    result = colour + std::to_string(shape);
  } else if (colour == 'B') {
    std::string colour = "\033[0;34mB";
    result = colour + std::to_string(shape);
  }

  return result;
}
