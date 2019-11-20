#ifndef BUTTON_H
#define BUTTON_H

#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>

class Button
{
    public:
        Button() = default;
        Button(sf::Vector2f size, sf::Vector2f pos);
        Button(sf::Vector2f size, sf::Vector2f pos, sf::Font& font, char* text, sf::Color color);
        virtual ~Button();

        void move(sf::Vector2f distance);
        bool hovers(sf::Vector2f cursorPos) const;

        void Light();
        void Dark();

        sf::Vector2f getSize() const;
        sf::Vector2f getPosition() const;

        void render(sf::RenderTarget& window);

    private:
        sf::RectangleShape _buttonShape;
        sf::Text _buttonText;

        sf::Color _buttonColor;
};

#endif // BUTTON_H
