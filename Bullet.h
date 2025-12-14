#ifndef BULLET_H
#define BULLET_H

class Bullet {
private:
    int x, y;

public:
    Bullet(int x, int y);
    void update();
    void draw();
    bool isOffScreen(int maxY);
    int getX() { return x; }
    int getY() { return y; }
};

#endif
