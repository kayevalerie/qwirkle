
#include "Tile.h"

Tile::Tile() : colour(Colour::NONE), shape(Shape::NONE) {}

Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape) {
  // setTile(true);
}

Tile::Tile(const Tile& toCopy) : colour(toCopy.colour), shape(toCopy.shape) {
  // setTile(true);
}

Colour Tile::getColour() { return colour; }

Shape Tile::getShape() { return shape; }

// void Tile::setTile(bool isSet) { tile = std::make_shared<bool>(isSet); }

bool Tile::equals(Tile tile) {
  return colour == tile.colour && shape == tile.shape;
}

std::string Tile::toString() {
  // todo: match other colors to have bg color instead

  std::string colourCode = " ";
  std::string shapeCode = " ";

  if (colour != Colour::NONE &&
      shape != Shape::NONE) {  // this tile has been initialized
    shapeCode = std::to_string(int(shape));

    if (colour == Colour::RED)
      colourCode = "\033[0;31mR";
    else if (colour == Colour::ORANGE)
      colourCode =
          "\033[48;2;255;165;0mO";  // source
                                    // https://stackoverflow.com/questions/32573654/is-there-a-way-to-create-an-orange-color-from-ansi-escape-characters
    else if (colour == Colour::YELLOW)
      colourCode = "\033[0;33mY";
    else if (colour == Colour::GREEN)
      colourCode = "\033[0;32mG";
    else if (colour == Colour::PURPLE)
      colourCode = "\033[0;35mP";
    else if (colour == Colour::BLUE)
      colourCode = "\033[0;34mB";
  }

  return colourCode + shapeCode + "\033[0;39m";
}
