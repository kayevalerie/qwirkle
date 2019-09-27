#include "Player.h"
#include <cstring>
#include <string>

Player::Player(std::string name, int points, std::string contents)
    : name(name), points(points), tiles(new LinkedList()) {
  setHand(contents);
}

Player::~Player() { clear(); }

void Player::clear() { delete tiles; }

void Player::setHand(std::string hand) {
  // todo
}

void Player::setPoints(int points) {
  // todo
}

std::string Player::getName() { return name; }

int Player::getPoints() { return points; }

LinkedList* Player::getHand() { return tiles; }