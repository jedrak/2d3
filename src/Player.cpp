//
// Created by jedra on 20.10.2019.
//

#include "Player.h"

#include <utility>

void Player::setSpeedX(float speedX) {
    Player::speedX = speedX;
}

void Player::setSpeedY(float speedY) {
    Player::speedY = speedY;
}

Player::Player() : GameObject(), speedX(0), speedY(0) {}

Player::Player(float x, float y) : GameObject(x, y), speedX(0), speedY(0){}

void Player::update() {
    this->setX(this->getX() + speedX );
    this->setY(this->getY() + speedY );
}

void Player::start() {
    //    this->setX(0);
    //    this->setY(0);
    //    this->speedX = 0;
    //    this->speedY = 0;
}

Player::~Player() {

}

Player::Player(float x, float y, Shape s, float speedX, float speedY) : GameObject(x, y, s), speedX(speedX),
                                                                        speedY(speedY) {}




