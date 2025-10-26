#include <iostream>
#include <SFML/Graphics.hpp>

class Paddle {
    public:
        double x = 500.f;
        double y = 750.f;
        float dir = 0.f;
        float scaleX = 2;
        float scaleY = 2;
        int speed = 700;
        bool start = false;
        sf::Texture paddleTexture;
        std::string paddleTexturePath = "./Assets/Sprites/paddle.png";
        sf::Sprite paddleSprite;

    void load() {
        if (!paddleTexture.loadFromFile(paddleTexturePath)) {
            std::cerr << "Error loading Paddle Texture.\n";
        }
        paddleSprite.setTexture(paddleTexture);
        paddleSprite.setPosition(x, y);
        paddleSprite.setRotation(dir);
        paddleSprite.setScale(scaleX, scaleY);
        sf::FloatRect bounds = paddleSprite.getLocalBounds();
        paddleSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    void draw(sf::RenderWindow &window) {
        if (!start && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            start = true;
        }
        paddleSprite.setPosition(x, y);
        window.draw(paddleSprite);
    }

    void move(float deltaSeconds, int screenWidth) {
        if (start) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                if (x > 90) {
                    x -= speed * deltaSeconds;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if (x < screenWidth - 90) {
                    x += speed * deltaSeconds;
                }
            }
        }

    }
};
