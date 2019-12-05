#ifndef CANVAS_H
#define CANVAS_H

#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>

class Canvas
{
    public:
        Canvas(sf::Vector2u size, sf::Color canvasColor,const sf::Font& font, std::string text = "", sf::Color textColor = sf::Color::White);
        Canvas(sf::Vector2u size, std::string path);
        Canvas(sf::Vector2u size, sf::Color canvasColor);
        virtual ~Canvas();

        void render(sf::RenderTarget& window);
        void move(sf::Vector2f distance);

        sf::Vector2f getSize() const;
        sf::Vector2f getPosition() const;
        sf::FloatRect getGlobalBounds() const;

    private:
        sf::RectangleShape _canvasShape;
        sf::Text _canvasTitle;
        sf::Texture _canvasTexture;
};

#endif // CANVAS_H
