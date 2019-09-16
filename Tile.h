
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
  Colour colour;
  Shape shape;

 public:
  Tile(Colour colour, Shape shape);
  Colour getColour();
  Shape getShape();
  bool equals(Tile* tile);
};

#endif  // ASSIGN2_TILE_H
