#include "Enemy.h"

Enemy::Enemy(sf::RectangleShape &platform)
{
    enemyShape.setSize(sf::Vector2f(50.f, 50.f));
    enemyShape.setPosition(sf::Vector2f(platform.getPosition().x + platform.getSize().x/2.f, platform.getPosition().y - enemyShape.getSize().y));
    enemyShape.setFillColor(sf::Color::Green);

    movingRange.x = platform.getPosition().x;
    movingRange.y = platform.getPosition().x + platform.getSize().x;
    speed = 5.f;

    initVariables();
}

Enemy::Enemy(const sf::Vector2f &Position,const sf::Vector2f &Range)
{
    enemyShape.setSize(sf::Vector2f(50.f, 50.f));
    enemyShape.setPosition(Position);
    enemyShape.setFillColor(sf::Color::Red);

    movingRange = Range;
    speed = 5.f;

    initVariables();
}

Enemy::Enemy(float *enemyParams)
{
    enemyShape.setSize(sf::Vector2f(50.f,50.f));
    enemyShape.setPosition(enemyParams[0],enemyParams[1]);
    enemyShape.setFillColor(sf::Color::Red);

    movingRange = {enemyParams[2], enemyParams[3]};
    speed = 5.f;

    initVariables();
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::initVariables()
{
    enemyShape.setFillColor(sf::Color::Blue);

    redHealthBar.setSize(sf::Vector2f(50.f, 5.f));
    redHealthBar.setPosition(enemyShape.getPosition().x, enemyShape.getPosition().y + 5.f);
    redHealthBar.setFillColor(sf::Color::Red);

    greenHealthBar.setSize(redHealthBar.getSize());
    greenHealthBar.setPosition(redHealthBar.getPosition());
    greenHealthBar.setFillColor(sf::Color::Green);

    maxHP = 3;
    currHP = maxHP;
}

void Enemy::update()
{
    if(enemyShape.getPosition().x < movingRange.x || enemyShape.getPosition().x + enemyShape.getSize().x > movingRange.y)
        speed *= -1;

    enemyShape.move(speed, 0);

    redHealthBar.setPosition(enemyShape.getPosition());
    greenHealthBar.setPosition(enemyShape.getPosition());
}

void Enemy::render(sf::RenderTarget& window)
{
    window.draw(enemyShape);

    window.draw(redHealthBar);
    window.draw(greenHealthBar);
}

sf::FloatRect Enemy::getGlobalBounds()  { return enemyShape.getGlobalBounds(); }
size_t Enemy::getHP()                   { return currHP;                       }

void Enemy::setHP(size_t newHP)         { currHP = newHP;
                                          greenHealthBar.setSize(sf::Vector2f(redHealthBar.getSize().x * (currHP/float(maxHP)), redHealthBar.getSize().y)); }

