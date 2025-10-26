#include <iostream>
#include <SFML/Graphics.hpp>

class StartMessage {
    public:
        int x = 330;
        int y = 550;
        float fontSize = 30;
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
        text.setString("Press Space To Start");
    }

    void draw(sf::RenderWindow &window) {
        window.draw(text);
    }
};
