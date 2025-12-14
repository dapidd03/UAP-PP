Enemy.h

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
private:
    int x, y;
    int speed;

public:
    Enemy(int x, int y, int speed);
    void update();
    void draw();
    bool isOffScreen(int maxY);
    int getX() { return x; }
    int getY() { return y; }
};

#endif
