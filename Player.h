Player.h

#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int x, y;

public:
    Player(int x, int y);
    void update();
    void draw();
    void moveLeft();
    void moveRight(int maxX);
    int getX() { return x; }
    int getY() { return y; }
};

#endif
