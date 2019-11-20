#ifndef CANVAS_H
#define CANVAS_H

#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>

class Canvas
{
    public:
        Canvas(sf::Vector2u size, sf::Color canvasColor,const sf::Font& font, std::string text = "", sf::Color textColor = sf::Color::White);
        virtual ~Canvas();

        void render(sf::RenderTarget& window);
        void move(sf::Vector2f distance);

        sf::Vector2f getSize() const;
        sf::Vector2f getPosition() const;

    private:
        sf::RectangleShape _canvasShape;
        sf::Text _canvasTitle;
};

#endif // CANVAS_H
