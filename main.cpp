#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "./Code/paddle.cpp"
#include "./Code/brick.cpp"
#include "./Code/ball.cpp"
#include "./Code/startMsg.cpp"
#include "./Code/deadMsg.cpp"
#include "./Code/winMsg.cpp"

struct BrickGrid {
    const int ROWS = 9;
    const int COLLUMS = 10;
};

void restart(Paddle &paddle, std::vector<std::vector<Brick>> &bricks, BrickGrid &brickGrid, std::mt19937 &gen, Ball &ball) {
    paddle.x = 500;
    paddle.start = false;
    ball.x = 500;
    ball.y = 630;
    ball.dir = 70;
    ball.speed = 400;
    for (int i = 0; i < brickGrid.ROWS; i += 1) {
        for (int j = 0; j < brickGrid.COLLUMS; j++) {
            std::uniform_int_distribution<> distrib(0, 3);
            int num = distrib(gen);
            if (num != 1) {
                Brick brick = Brick();
                brick.x = (i * 100) + 50;
                brick.y = (j * 50) + 20;
                brick.load();
                brick.loaded = true;
                bricks[i].push_back(brick);
            }
        }
    }
}

int main() {
    bool died = false;
    int screenWidth = 1000;
    int screenHeight = 850;
    std::random_device rd;
    std::mt19937 gen(rd());
    sf::Color backgroundColor(0, 0, 0);
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Brick Breaker");
    window.setVerticalSyncEnabled(true);
    sf::Clock deltaClock;

    Paddle paddle = Paddle();
    paddle.load();

    Ball ball = Ball();
    ball.load();

    StartMessage startMsg = StartMessage();
    startMsg.load();

    DeadMessage deadMsg = DeadMessage();
    deadMsg.load();

    WinMessage winMsg = WinMessage();
    winMsg.load();

    BrickGrid brickGrid = BrickGrid();
    std::vector<std::vector<Brick>> bricks;
    for (int i = 0; i < brickGrid.ROWS; i += 1) {
        std::vector<Brick> row;
        for (int j = 0; j < brickGrid.COLLUMS; j++) {
            std::uniform_int_distribution<> distrib(0, 3);
            int num = distrib(gen);
            if (num != 1) {
                Brick brick = Brick();
                brick.x = (i * 100) + 50;
                brick.y = (j * 50) + 20;
                brick.load();
                brick.loaded = true;
                row.push_back(brick);
            }
        }
        bricks.push_back(row);
    }
    while (window.isOpen()) {
        sf::Event event;
        sf::Time deltaTime = deltaClock.restart();
        float deltaSeconds = deltaTime.asSeconds();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(backgroundColor);

        if (!paddle.start) {
            startMsg.draw(window);
        }

        paddle.draw(window);
        paddle.move(deltaSeconds, screenWidth);

        for (auto &row : bricks) {
            for (auto &brick : row) {
                bool brickCollided = ball.brickCollide(brick.brickSprite);
                if (brickCollided) {
                    brick.remove = true;
                    ball.dir = -ball.dir;
                    ball.speed *= 1.005;
                    ball.y += 10;
                }
                brick.draw(window);
            }
        }
        for (std::vector<Brick> &row: bricks) {
            row.erase(std::remove_if(row.begin(), row.end(), [](const Brick& brick) { return brick.remove; }),row.end());
        }

        bool allEmpty = true;
        for (std::vector<Brick> &row: bricks) {
            if (!row.empty()) {
                allEmpty = false;
                break;
            }
        }
        if (allEmpty) {
            winMsg.draw(window);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                restart(paddle, bricks, brickGrid, gen, ball);
            }
        }
        ball.draw(window);
        if (paddle.start) {
            ball.move(deltaSeconds);
        }
        ball.wallCollide(screenWidth);
        bool paddleCollided = ball.paddleCollide(paddle.paddleSprite);
        if (paddleCollided) {
            ball.dir = -ball.dir;
            ball.y -= 10;
            ball.speed *= 1.005;
        }
        died = ball.die(screenHeight);
        if (died && !allEmpty) {
            deadMsg.draw(window);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                restart(paddle, bricks, brickGrid, gen, ball);
            }
        }
        window.display();
    }
    return 0;
}
