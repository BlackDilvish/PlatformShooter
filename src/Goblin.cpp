#include "Goblin.h"

Goblin::Goblin(sf::RectangleShape &platform) : Enemy(platform)
{
    setAnimation("Assets/Images/GoblinWalk.png", 23, {450.f, 450.f}, 0.03f);
}

Goblin::Goblin(const sf::Vector2f &Position,const sf::Vector2f &Range) : Enemy(Position, Range)
{
    setAnimation("Assets/Images/GoblinWalk.png", 23, {450.f, 450.f}, 0.03f);
}

Goblin::Goblin(float *enemyParams) : Enemy(enemyParams)
{
    setAnimation("Assets/Images/GoblinWalk.png", 23, {450.f, 450.f}, 0.03f);
}

Goblin::~Goblin()
{
    freeAnimation();
}

