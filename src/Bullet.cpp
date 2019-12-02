#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir, float radius, sf::Color color, float lifetime, float speed)
    : _bulletSpeed(speed), _bulletTrajectory(dir*speed), _lifeTimer(0), _periodOfLife(lifetime)
{
    _bulletShape.setRadius(radius);
    _bulletShape.setPosition(pos);
    _bulletShape.setFillColor(color);
}

void Bullet::Update()
{
    UpdateTime();

    _bulletShape.move(_bulletTrajectory);

    CollisionWithPlatforms();
}

void Bullet::CollisionWithPlatforms()
{
    for(size_t i=0; i<PlatformsManager::getSize(); i++)
        if(_bulletShape.getGlobalBounds().intersects(PlatformsManager::getPlatform(i).getGlobalBounds()))
            _lifeTimer += _periodOfLife;
}

void Bullet::UpdateTime()
{
    _lifeTimer += _clock.getElapsedTime().asSeconds();
    _clock.restart();
}

void Bullet::Render(sf::RenderTarget& window) const
{
    window.draw(_bulletShape);
}

bool Bullet::Dead()
{
    return _lifeTimer > _periodOfLife;
}

sf::FloatRect Bullet::getGlobalBounds() const
{
    return _bulletShape.getGlobalBounds();
}

bool Bullet::Hit(sf::FloatRect hitbox) const
{
    return _bulletShape.getGlobalBounds().intersects(hitbox);
}
