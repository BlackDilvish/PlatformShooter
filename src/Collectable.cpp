#include "Collectable.h"

Collectable::Collectable(sf::Vector2f size, sf::Vector2f pos, size_t value = 1)
{
    _shape.setSize(size);
    _shape.setPosition(pos);

    _collectTexture = NULL;
    _collectAnimation = NULL;

    _value = value;
    _velocity = 0.4f;

    _rangeLimit = 10.f;
    _topRange = pos.y - _rangeLimit;
    _bottomRange = pos.y + _rangeLimit;
}

void Collectable::setTexture(char* path)
{
    _collectTexture = new sf::Texture;
    _collectTexture->loadFromFile(path);
}

void Collectable::setAnimation(char* path,size_t numberOfFrames,sf::Vector2f sizeOfFrame,float cooldown)
{
    _collectAnimation = new Animation(path,numberOfFrames,sizeOfFrame,_shape.getSize(),cooldown,true,false);
    _collectAnimation->setPosition(_shape.getPosition());
}

void Collectable::Update()
{
    if(_shape.getPosition().y < _topRange || _shape.getPosition().y > _bottomRange)
        _velocity*=-1;

    _shape.move(0, _velocity);

    if(_collectAnimation)
    {
        _collectAnimation->setPosition(_shape.getPosition());
        _collectAnimation->update();
    }


}

void Collectable::Render(sf::RenderTarget& window) const
{
    if(_collectAnimation)
        _collectAnimation->render(window);
    else
        window.draw(_shape);
}

sf::FloatRect Collectable::getGlobalBounds() const
{
    return _shape.getGlobalBounds();
}

void Collectable::deleteTexture()
{
    delete _collectTexture;
}

void Collectable::deleteAnimation()
{
    delete _collectAnimation;
}
