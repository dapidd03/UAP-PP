#include "Game.h"
#include <unistd.h> // Untuk usleep
#include <cstdlib>  // Untuk rand()
#include <ctime>   // Untuk srand()

Game::Game() : player(0, 0), score(0), state(MENU), enemySpawnTimer(0), enemySpeed(1), frameCount(0) {
    init();
}

Game::~Game() {
    endwin();
}

void Game::init() {
    initscr();          // Inisialisasi ncurses
    noecho();           // Tidak echo input
    cbreak();           // Input langsung tanpa enter
    keypad(stdscr, TRUE); // Aktifkan keypad untuk arrow keys
    nodelay(stdscr, TRUE); // Input non-blocking
    curs_set(0);        // Sembunyikan cursor
    getmaxyx(stdscr, height, width); // Dapatkan ukuran layar
    player = Player(width / 2, height - 2); // Posisi player di bawah
    srand(time(NULL));  // Seed random
}

void Game::run() {
    while (true) {
        switch (state) {
            case MENU:
                showMenu();
                break;
            case PLAYING:
                update();
                draw();
                break;
            case GAME_OVER:
                showGameOver();
                break;
        }
        usleep(1000000 / 30); // 30 FPS
    }
}

void Game::update() {
    handleInput();
    checkCollisions();

    // Update player
    player.update();

    // Update bullets
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->update();
        if (it->isOffScreen(height)) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }

    // Update enemies
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        it->update();
        if (it->isOffScreen(height)) {
            state = GAME_OVER; // Game over jika enemy mencapai bawah
            return;
        } else {
            ++it;
        }
    }

    // Spawn enemy setiap 30 frame (sesuaikan untuk kesulitan)
    enemySpawnTimer++;
    if (enemySpawnTimer >= 30) {
        spawnEnemy();
        enemySpawnTimer = 0;
    }

    // Tingkatkan kecepatan enemy setiap 100 skor
    if (score > 0 && score % 100 == 0 && enemySpeed < 5) {
        enemySpeed++;
    }

    frameCount++;
}

void Game::draw() {
    clear(); // Bersihkan layar

    // Tampilkan skor
    mvprintw(0, 0, "Score: %d", score);

    // Draw player
    player.draw();

    // Draw bullets
    for (auto& bullet : bullets) {
        bullet.draw();
    }

    // Draw enemies
    for (auto& enemy : enemies) {
        enemy.draw();
    }

    refresh(); // Refresh layar
}

void Game::handleInput() {
    int ch = getch();
    switch (ch) {
        case 'a':
        case 'A':
        case KEY_LEFT:
            player.moveLeft();
            break;
        case 'd':
        case 'D':
        case KEY_RIGHT:
            player.moveRight(width);
            break;
        case ' ':
            bullets.push_back(Bullet(player.getX(), player.getY() - 1));
            break;
        case 'q':
        case 'Q':
            state = GAME_OVER;
            break;
    }
}

void Game::checkCollisions() {
    // Bullet vs Enemy
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
        bool hit = false;
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
            if (bulletIt->getX() == enemyIt->getX() && bulletIt->getY() == enemyIt->getY()) {
                // Collision detected
                enemyIt = enemies.erase(enemyIt);
                hit = true;
                score += 10; // Tambah skor
                break;
            } else {
                ++enemyIt;
            }
        }
        if (hit) {
            bulletIt = bullets.erase(bulletIt);
        } else {
            ++bulletIt;
        }
    }

    // Enemy vs Player
    for (auto& enemy : enemies) {
        if (enemy.getX() == player.getX() && enemy.getY() == player.getY()) {
            state = GAME_OVER;
            return;
        }
    }
}

void Game::spawnEnemy() {
    int x = rand() % width;
    enemies.push_back(Enemy(x, 0, enemySpeed));
}

void Game::showMenu() {
    clear();
    mvprintw(height / 2 - 2, width / 2 - 10, "SPACE SHOOTER");
    mvprintw(height / 2, width / 2 - 15, "Press ENTER to Start");
    mvprintw(height / 2 + 2, width / 2 - 10, "Controls: A/D or Arrows to move, SPACE to shoot, Q to quit");
    refresh();
    int ch = getch();
    if (ch == '\n' || ch == KEY_ENTER) {
        state = PLAYING;
        // Reset game state
        enemies.clear();
        bullets.clear();
        score = 0;
        enemySpawnTimer = 0;
        enemySpeed = 1;
        frameCount = 0;
    }
}

void Game::showGameOver() {
    clear();
    mvprintw(height / 2 - 2, width / 2 - 10, "GAME OVER");
    mvprintw(height / 2, width / 2 - 10, "Score: %d", score);
    mvprintw(height / 2 + 2, width / 2 - 20, "Press ENTER to Restart or Q to Quit");
    refresh();
    int ch = getch();
    if (ch == '\n' || ch == KEY_ENTER) {
        state = MENU;
    } else if (ch == 'q' || ch == 'Q') {
        endwin();
        exit(0);
    }
}