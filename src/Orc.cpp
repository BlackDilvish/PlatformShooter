#include "Orc.h"

Orc::Orc(sf::RectangleShape &platform) : Enemy(platform)
{
    setAnimation((char*)"Assets/Images/OrcWalk.png", 24, {112.5f, 113.f}, 0.03f);
}

Orc::Orc(const sf::Vector2f &Position,const sf::Vector2f &Range) : Enemy(Position, Range)
{
    setAnimation((char*)"Assets/Images/OrcWalk.png", 24, {112.5f, 113.f}, 0.03f);
}

Orc::Orc(float *enemyParams) : Enemy(enemyParams)
{
    setAnimation((char*)"Assets/Images/OrcWalk.png", 24, {112.5f, 113.f}, 0.03f);
}

Orc::~Orc()
{
    freeAnimation();
}

