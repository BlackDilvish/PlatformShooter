#ifndef GOBLIN_H
#define GOBLIN_H

#include"Enemy.h"

class Goblin : public Enemy
{
    public:
        Goblin(sf::RectangleShape &platform);
        Goblin(const sf::Vector2f &Position,const sf::Vector2f &Range);
        Goblin(float *enemyParams);
        virtual ~Goblin();

    protected:

    private:
};

#endif // GOBLIN_H
