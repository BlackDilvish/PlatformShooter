#include "Enemy.h"

Enemy::Enemy(sf::RectangleShape &platform)
{
    enemyShape.setSize(sf::Vector2f(50.f, 50.f));
    enemyShape.setPosition(sf::Vector2f(platform.getPosition().x + platform.getSize().x/2.f, platform.getPosition().y - enemyShape.getSize().y));
    enemyShape.setFillColor(sf::Color::Green);

    bindedPlatform = &platform;
    speed = 5.f;
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::update()
{
    if(enemyShape.getPosition().x < bindedPlatform->getPosition().x || enemyShape.getPosition().x + enemyShape.getSize().x > bindedPlatform->getPosition().x + bindedPlatform->getSize().x)
        speed *= -1;

    enemyShape.move(speed, 0);
}

void Enemy::render(sf::RenderTarget& window)
{
    window.draw(enemyShape);
}

sf::FloatRect Enemy::getGlobalBounds()
{
    return enemyShape.getGlobalBounds();
}
