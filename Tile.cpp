
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape) {}

Tile::Tile(Tile& toCopy) : colour(toCopy.getColour()), shape(toCopy.getColour()) {}

Colour Tile::getColour() { return colour; }

Shape Tile::getShape() { return shape; }

bool Tile::equals(Tile *tile) {
  return colour == tile->getColour() && shape == tile->getShape();
}

std::string Tile::toString() {
    if(colour == 'R'){
        std::string colour = "\033[0;31mR";
        return colour + std::to_string(shape);
    }
    if(colour == 'O'){
        std::string colour = "\033[0;37mO";
        return colour + std::to_string(shape);
    }
    if(colour == 'Y'){
        std::string colour = "\033[0;33mY";
        return colour + std::to_string(shape);
    }
    if(colour == 'G'){
        std::string colour = "\033[0;32mG";
        return colour + std::to_string(shape);
    }
    if(colour == 'P'){
        std::string colour = "\033[0;35mP";
        return colour + std::to_string(shape);
    }
    if(colour == 'B'){
        std::string colour = "\033[0;34mB";
        return colour + std::to_string(shape);
    }
}
