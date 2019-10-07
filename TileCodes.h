
#ifndef ASSIGN1_TILECODES_H
#define ASSIGN1_TILECODES_H

#include <array>
#include <string>

#define COLOUR_SIZE 6
#define SHAPE_SIZE 6

enum class Colour {
  RED = 'R',
  ORANGE = 'O',
  YELLOW = 'Y',
  GREEN = 'G',
  BLUE = 'B',
  PURPLE = 'P',
  NONE = 'N'
};

enum class Shape { NONE = 0, CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };

extern const std::array<Colour, COLOUR_SIZE> colours;
extern const std::array<Shape, SHAPE_SIZE> shapes;
bool isCodeValid(std::string code);

#endif  // ASSIGN1_TILECODES_H
