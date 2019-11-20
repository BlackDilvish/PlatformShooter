#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f pos)
{
    _buttonShape.setSize(size);
    _buttonShape.setPosition(pos);
}

Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Font& font, char* text, sf::Color color)
{
    _buttonShape.setSize(size);
    _buttonShape.setPosition(pos);

    _buttonText.setFont(font);
    _buttonText.setString(text);
    _buttonText.setCharacterSize(63);

    sf::Vector2f shift = sf::Vector2f(-size.x + _buttonText.findCharacterPos(_buttonText.getString().getSize()).x - _buttonText.findCharacterPos(0).x, 0)/2.f;
    _buttonText.setPosition(pos - shift);

    _buttonColor = color;
}

Button::~Button()
{

}

void Button::move(sf::Vector2f distance)
{
    _buttonShape.move(distance);
    _buttonText.move(distance);
}

bool Button::hovers(sf::Vector2f cursorPos) const
{
    return _buttonShape.getGlobalBounds().contains(cursorPos);
}

void Button::Light()
{
    _buttonShape.setFillColor(_buttonColor);
}

void Button::Dark()
{
    _buttonShape.setFillColor(sf::Color::White);
}

sf::Vector2f Button::getSize() const
{
    return _buttonShape.getSize();
}

sf::Vector2f Button::getPosition() const
{
    return _buttonShape.getPosition();
}

void Button::render(sf::RenderTarget& window)
{
    window.draw(_buttonShape);
    window.draw(_buttonText);
}


