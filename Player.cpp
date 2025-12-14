Player.cpp

#include "Player.h"
#include <ncurses.h>

Player::Player(int x, int y) : x(x), y(y) {}

void Player::update() {
    // Player update logic (gerakan sudah di handleInput di Game)
}

void Player::draw() {
    mvaddch(y, x, 'A'); // Gambar player sebagai 'A'
}

void Player::moveLeft() {
    if (x > 0) x--;
}

void Player::moveRight(int maxX) {
    if (x < maxX - 1) x++;
}
