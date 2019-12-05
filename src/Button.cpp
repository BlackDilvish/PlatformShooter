#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f pos)
{
    _buttonShape.setSize(size);
    _buttonShape.setPosition(pos);
}

Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Font& font, std::string text, sf::Color lightColor, sf::Color defaultColor, size_t charSize)
    : _lightColor(lightColor), _defaultColor(defaultColor)
{
    _buttonShape.setSize(size);
    _buttonShape.setPosition(pos);
    _buttonShape.setFillColor(defaultColor);

    _buttonText.setFont(font);
    _buttonText.setString(text);
    _buttonText.setCharacterSize(charSize);

    sf::Vector2f shift = sf::Vector2f(-size.x + _buttonText.findCharacterPos(_buttonText.getString().getSize()).x - _buttonText.findCharacterPos(0).x, 0)/2.f;
    _buttonText.setPosition(pos - shift);
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
    if(_buttonShape.getFillColor() == sf::Color::Transparent)
        _buttonText.setFillColor(_lightColor);
    else
        _buttonShape.setFillColor(_lightColor);
}

void Button::Dark()
{
    if(_buttonShape.getFillColor() == sf::Color::Transparent)
        _buttonText.setFillColor(sf::Color::White);
    else
        _buttonShape.setFillColor(_defaultColor);
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


