#include "Orc.h"

Orc::Orc(sf::RectangleShape &platform) : Enemy(platform)
{
    setAnimation("Assets/Images/OrcWalk.png", 24, {450.f, 450.f}, 0.03f);
}

Orc::Orc(const sf::Vector2f &Position,const sf::Vector2f &Range) : Enemy(Position, Range)
{
    setAnimation("Assets/Images/OrcWalk.png", 24, {450.f, 450.f}, 0.03f);
}

Orc::Orc(float *enemyParams) : Enemy(enemyParams)
{
    setAnimation("Assets/Images/OrcWalk.png", 24, {450.f, 450.f}, 0.03f);
}

Orc::~Orc()
{
    freeAnimation();
}

