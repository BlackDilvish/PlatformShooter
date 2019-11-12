#include "InteractionObject.h"

InteractionObject::InteractionObject(sf::Vector2f pos, sf::Vector2f size)
{
    objShape.setSize(size);
    objShape.setPosition(pos);
}

InteractionObject::~InteractionObject()
{

}

void InteractionObject::setTexture(std::string path)
{
    objTex.loadFromFile(path);
    objShape.setTexture(&objTex);
}

void InteractionObject::Interact()
{

}

void InteractionObject::updatePlayerCollision(Player &player)
{
    if(player.getGlobalBounds().intersects(objShape.getGlobalBounds()))
    {
        objShape.setFillColor(sf::Color::Yellow);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            Interact();
    }
    else
        objShape.setFillColor(sf::Color::White);
}

void InteractionObject::update(Player &player)
{
    updatePlayerCollision(player);
}

void InteractionObject::render(sf::RenderTarget &window)
{
    window.draw(objShape);
}
