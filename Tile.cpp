
#include "Tile.h"

Tile::Tile() : colour(Colour::NONE), shape(Shape::NONE) {}

Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape) {}

Tile::Tile(const Tile& toCopy) : colour(toCopy.colour), shape(toCopy.shape) {}

Colour Tile::getColour() { return colour; }

Shape Tile::getShape() { return shape; }

bool Tile::equals(Tile tile) {
  return colour == tile.colour && shape == tile.shape;
}

std::string Tile::toString() {
  std::string colourCode = " ";
  std::string shapeCode = " ";

  if (colour != Colour::NONE &&
      shape != Shape::NONE) {  // if this tile has been initialized
    shapeCode = std::to_string(int(shape));

    if (colour == Colour::RED)
      colourCode = "\e[31mR";
    else if (colour == Colour::ORANGE)
      colourCode = "\e[93mO";
    else if (colour == Colour::YELLOW)
      colourCode = "\e[33mY";
    else if (colour == Colour::GREEN)
      colourCode = "\e[32mG";
    else if (colour == Colour::PURPLE)
      colourCode = "\e[35mP";
    else if (colour == Colour::BLUE)
      colourCode = "\e[34mB";
  }

  return colourCode + shapeCode + "\e[0m";
}
