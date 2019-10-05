
#include "Tile.h"

Tile::Tile() {}

Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape) {}

Tile::Tile(const Tile& toCopy) : colour(toCopy.colour), shape(toCopy.shape) {}

Colour Tile::getColour() { return colour; }

Shape Tile::getShape() { return shape; }

bool Tile::equals(Tile tile) {
  return colour == tile.colour && shape == tile.shape;
}

std::string Tile::toString() {
  std::string colourCode;

  if (colour == Colour::RED)
    colourCode = "\033[0;31mR";
  else if (colour == Colour::ORANGE)
    colourCode = "\033[0;33mO";
  else if (colour == Colour::YELLOW)
    colourCode = "\033[1;33mY";
  else if (colour == Colour::GREEN)
    colourCode = "\033[0;32mG";
  else if (colour == Colour::PURPLE)
    colourCode = "\033[0;35mP";
  else if (colour == Colour::BLUE)
    colourCode = "\033[0;34mB";

  return colourCode + std::to_string(int(shape)) + "\033[39m";
}
