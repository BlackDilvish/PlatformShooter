#include "Canvas.h"

Canvas::Canvas(sf::Vector2u size, sf::Color canvasColor,const sf::Font& font, std::string text, sf::Color textColor)
{
    _canvasShape.setSize(sf::Vector2f(size));
    _canvasShape.setFillColor(canvasColor);

    _canvasTitle.setFont(font);
    _canvasTitle.setCharacterSize(63);
    _canvasTitle.setFillColor(textColor);
    _canvasTitle.setString(text);

    sf::Vector2f shift = sf::Vector2f(_canvasTitle.findCharacterPos(_canvasTitle.getString().getSize()).x - _canvasTitle.findCharacterPos(0).x, getSize().y/1.5f)/2.f;
    _canvasTitle.setPosition(getSize()/2.f - shift);
}

Canvas::Canvas(sf::Vector2u size, std::string path)
{
    _canvasTexture.loadFromFile(path);

    _canvasShape.setSize(sf::Vector2f(size));
    _canvasShape.setTexture(&_canvasTexture);
}

Canvas::~Canvas()
{

}

sf::Vector2f Canvas::getSize() const
{
    return _canvasShape.getSize();
}

sf::Vector2f Canvas::getPosition() const
{
    return _canvasShape.getPosition();
}

void Canvas::render(sf::RenderTarget& window)
{
    window.draw(_canvasShape);
    window.draw(_canvasTitle);
}

void Canvas::move(sf::Vector2f distance)
{
    _canvasShape.move(distance);
    _canvasTitle.move(distance);
}
