#include "Player.h"
#include <cstring>
#include <string>

Player::Player(std::string name, int points, LinkedList* tiles)
    : name(name), points(points), hand(new LinkedList(*tiles)) {}

Player::Player(std::string name) : name(name), points(0), hand(nullptr) {}

Player::~Player() { clear(); }

void Player::clear() { delete hand; }

void Player::setPoints(int points) { this->points = points; }

std::string Player::getName() { return name; }

int Player::getPoints() { return points; }

LinkedList* Player::getHand() { return hand; }

void Player::setHand(LinkedList* tiles) {
  hand = new LinkedList(*tiles);
  // not sure if a copy needed
}
