#include <iostream>
#include <SFML/Graphics.hpp>

class WinMessage {
    public:
        int x = 240;
        int y = 615;
        float fontSize = 40;
        std::string fontPath = "./Assets/Fonts/pixel.ttf";
        sf::Font font;
        sf::Text text;

    void load() {
        if (!font.loadFromFile(fontPath)) {
            std::cerr << "Error loading Font.\n";
        }
        text.setFont(font);
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::White);
        text.setPosition(x, y);
        text.setString("You Win!. R to restart");
    }

    void draw(sf::RenderWindow &window) {
        window.draw(text);
    }
};
