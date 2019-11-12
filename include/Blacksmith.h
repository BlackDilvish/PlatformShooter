#ifndef BLACKSMITH_H
#define BLACKSMITH_H

#include"Npc.h"

class Blacksmith : public Npc
{
    public:
        Blacksmith(sf::Vector2f Position,const sf::Vector2f size = {90.f,90.f});
        virtual ~Blacksmith();

    protected:

    private:
};

#endif // BLACKSMITH_H
