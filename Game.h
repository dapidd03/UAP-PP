#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ncurses.h>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

enum GameState { MENU, PLAYING, GAME_OVER };

class Game {
private:
    int width, height;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    int score;
    GameState state;
    int enemySpawnTimer;
    int enemySpeed;
    int frameCount;

public:
    Game();
    ~Game();
    void init();
    void run();
    void update();
    void draw();
    void handleInput();
    void checkCollisions();
    void spawnEnemy();
    void showMenu();
    void showGameOver();
};

#endif