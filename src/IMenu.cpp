#include "IMenu.h"

IMenu::IMenu()
{
    buttonSize(sf::Vector2f(100.f, 100.f));
    setFont("Assets/Fonts/Lato.ttf");
}

size_t IMenu::getStatus() const
{
    return _status;
}

void IMenu::setStatus(size_t newStatus)
{
    _status = newStatus;
}

sf::Font& IMenu::getFont() const
{
    return *_font;
}

void IMenu::setFont(std::string path)
{
    deleteFont();

    _font = new sf::Font;
    _font->loadFromFile(path);
}

void IMenu::deleteFont()
{
    if(!_font)
        delete _font;
    _font = NULL;
}

const sf::Vector2f& IMenu::buttonSize()
{
    return _buttonSize;
}

void IMenu::buttonSize(sf::Vector2f size)
{
    _buttonSize = size;
}
