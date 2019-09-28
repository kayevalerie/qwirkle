#include "Player.h"
#include <cstring>
#include <string>

Player::Player(std::string name, int points, LinkedList* tiles)
    : name(name), points(points), tiles(new LinkedList()) {
  setHand(contents);
}

Player::~Player() { clear(); }

void Player::clear() { delete tiles; }

void Player::setHand(LinkedList* tiles) {
  // todo
}

void Player::setPoints(int points) {
  points = points;
}

std::string Player::getName() { return name; }

int Player::getPoints() { return points; }

LinkedList* Player::getHand() { return tiles; }
