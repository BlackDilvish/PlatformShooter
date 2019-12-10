#include "Goblin.h"

Goblin::Goblin(sf::RectangleShape &platform) : Enemy(platform)
{
    setAnimation((char*)"Assets/Images/GoblinWalk.png", 23, {112.5f, 113.f}, 0.03f);
}

Goblin::Goblin(const sf::Vector2f &Position,const sf::Vector2f &Range) : Enemy(Position, Range)
{
    setAnimation((char*)"Assets/Images/GoblinWalk.png", 23, {112.5f, 113.f}, 0.03f);
}

Goblin::Goblin(float *enemyParams) : Enemy(enemyParams)
{
    setAnimation((char*)"Assets/Images/GoblinWalk.png", 23, {112.5f, 113.f}, 0.03f);
}

Goblin::~Goblin()
{
    freeAnimation();
}

