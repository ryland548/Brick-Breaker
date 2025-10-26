#include <iostream>
#include <SFML/Graphics.hpp>

class Brick {
    public:
        double x = 0.f;
        double y = 0.f;
        float dir = 0.f;
        float scaleX = 1.8;
        float scaleY = 1.8;
        bool remove = false;
        bool loaded = false;
        static sf::Texture brickTexture;
        std::string brickTexturePath = "./Assets/Sprites/brick.png";
        sf::Sprite brickSprite;

    void load() {
        if (!brickTexture.loadFromFile(brickTexturePath)) {
            std::cerr << "Error loading Brick Texture.\n";
        }
        brickSprite.setTexture(brickTexture);
        brickSprite.setPosition(x, y);
        brickSprite.setRotation(dir);
        brickSprite.setScale(scaleX, scaleY);
    }

    void draw(sf::RenderWindow &window) {
        brickSprite.setPosition(x, y);
        window.draw(brickSprite);
    }
};
sf::Texture Brick::brickTexture;
