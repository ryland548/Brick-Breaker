#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct Velocity {
    double x = 0;
    double y = 0;
};

class Ball {
    public:
        double x = 500.f;
        double y = 630.f;
        float dir = 70.f;
        float scaleX = 3;
        float scaleY = 3;
        Velocity ballVelocity = Velocity();
        int speed = 400;
        sf::Texture ballTexture;
        std::string ballTexturePath = "./Assets/Sprites/ball.png";
        sf::Sprite ballSprite;
        sf::SoundBuffer hitBuffer;
        std::string hitSoundPath = "./Assets/Audio/hit.wav";
        sf::Sound hitSound;

    void load() {
        if (!ballTexture.loadFromFile(ballTexturePath)) {
            std::cerr << "Error loading Ball Texture.\n";
        }
        if (!hitBuffer.loadFromFile(hitSoundPath)) {
            std::cerr << "Error loading Sound";
        }
        hitSound.setBuffer(hitBuffer);
        hitSound.setVolume(30.f);
        ballSprite.setTexture(ballTexture);
        ballSprite.setPosition(x, y);
        ballSprite.setRotation(dir);
        ballSprite.setScale(scaleX, scaleY);
        sf::FloatRect bounds = ballSprite.getLocalBounds();
        ballSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    void draw(sf::RenderWindow &window) {
        ballSprite.setPosition(x, y);
        window.draw(ballSprite);
    }

    void move(float dtSeconds) {
        double dirRadians = dir * (M_PI / 180.0);
        double deltaX = speed * cos(dirRadians);
        double deltaY = speed * sin(dirRadians);
        ballVelocity.x = deltaX * dtSeconds;
        ballVelocity.y = deltaY * dtSeconds;

        x += ballVelocity.x;
        y += ballVelocity.y;
    }

    bool paddleCollide(sf::Sprite paddleSprite) {
        if (ballSprite.getGlobalBounds().intersects(paddleSprite.getGlobalBounds())) {
            hitSound.play();
            return true;
        }
        return false;
    }

    void wallCollide(int screenWidth) {
        if (x > screenWidth - ballSprite.getGlobalBounds().width / 2) {
            dir = 180 - dir;
            x -= 2;
            hitSound.play();
        }
        if (x < 0 + ballSprite.getGlobalBounds().width / 2) {
            dir = 180 - dir;
            x += 2;
            hitSound.play();
        }
        if (y < 0 + ballSprite.getGlobalBounds().width / 2) {
            dir = -dir;
            y += 2;
            hitSound.play();
        }
    }

    bool brickCollide(sf::Sprite brickSprite) {
        if (ballSprite.getGlobalBounds().intersects(brickSprite.getGlobalBounds())) {
            hitSound.play();
            return true;
        }
        return false;
    }

    bool die(int screenHeight) {
        if (y > screenHeight + 80) {
            return true;
        }
        return false;
    }
};
