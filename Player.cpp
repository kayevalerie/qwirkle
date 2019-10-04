#include "Player.h"

Player::Player(std::string name, int points, LinkedList* tiles)
    : name(name), points(points), hand(new LinkedList(*tiles)) {}

Player::Player(std::string name) : name(name), points(0), hand(nullptr) {}

Player::~Player() { clear(); }

void Player::clear() { delete hand; }

std::string Player::getName() { return name; }

void Player::setPoints(int points) { this->points = points; }

int Player::getPoints() { return points; }

void Player::setHand(LinkedList* tiles) {
  hand = new LinkedList(*tiles);
  // not sure if a copy needed
}

LinkedList* Player::getHand() { return hand; }

void Player::drawTile(LinkedList* tileBag) {
  Tile* tile = tileBag->getFront();

  // delete from tileBag
  tileBag->deleteFront();

  // add to the player hand
  hand->addTile(tile);
}
