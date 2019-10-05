#include "TileCodes.h"

#include <algorithm>

const std::array<Colour, COLOUR_SIZE> colours = {
    Colour::RED,   Colour::ORANGE, Colour::YELLOW,
    Colour::GREEN, Colour::BLUE,   Colour::PURPLE};

const std::array<Shape, SHAPE_SIZE> shapes = {Shape::CIRCLE,  Shape::STAR_4,
                                              Shape::DIAMOND, Shape::SQUARE,
                                              Shape::STAR_6,  Shape::CLOVER};

bool isCodeValid(std::string code) {
  bool isColourValid =
      std::find(std::begin(colours), std::end(colours),
                static_cast<Colour>(code.at(0))) != std::end(colours);

  bool isShapeValid =
      std::find(std::begin(shapes), std::end(shapes),
                static_cast<Shape>(code.at(1) - '0')) != std::end(shapes);

  return isColourValid && isShapeValid;
}