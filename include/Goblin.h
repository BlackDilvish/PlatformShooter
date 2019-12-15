#ifndef GOBLIN_H
#define GOBLIN_H

#include"TexturesManager.h"
#include"Enemy.h"

class Goblin : public Enemy
{
    public:
        Goblin(sf::RectangleShape &platform);
        Goblin(const sf::Vector2f &Position,const sf::Vector2f &Range);
        Goblin(float *enemyParams);
        virtual ~Goblin();
};

#endif // GOBLIN_H
