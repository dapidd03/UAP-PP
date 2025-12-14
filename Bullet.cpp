#include "Bullet.h"
#include <ncurses.h>

Bullet::Bullet(int x, int y) : x(x), y(y) {}

void Bullet::update() {
    y--; // Gerak ke atas
}

void Bullet::draw() {
    mvaddch(y, x, '|'); // Gambar bullet sebagai '|'
}

bool Bullet::isOffScreen(int maxY) {
    return y < 0;
}
