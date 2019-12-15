#ifndef ORC_H
#define ORC_H

#include"Enemy.h"
#include"TexturesManager.h"

class Orc : public Enemy
{
    public:
        Orc(sf::RectangleShape &platform);
        Orc(const sf::Vector2f &Position,const sf::Vector2f &Range);
        Orc(float *enemyParams);
        virtual ~Orc();
};

#endif // ORC_H
