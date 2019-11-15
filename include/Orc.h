#ifndef ORC_H
#define ORC_H

#include"Enemy.h"

class Orc : public Enemy
{
    public:
        Orc(sf::RectangleShape &platform);
        Orc(const sf::Vector2f &Position,const sf::Vector2f &Range);
        Orc(float *enemyParams);
        virtual ~Orc();

    protected:

    private:
};

#endif // ORC_H
