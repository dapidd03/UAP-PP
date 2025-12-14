#include "Enemy.h"
#include <ncurses.h>

Enemy::Enemy(int x, int y, int speed) : x(x), y(y), speed(speed) {}

void Enemy::update() {
    y += speed; // Gerak ke bawah
}

void Enemy::draw() {
    mvaddch(y, x, 'V'); // Gambar enemy sebagai 'V'
}

bool Enemy::isOffScreen(int maxY) {
    return y >= maxY;
}
