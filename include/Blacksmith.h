#ifndef BLACKSMITH_H
#define BLACKSMITH_H

#include"Npc.h"
#include"TexturesManager.h"

class Blacksmith : public Npc
{
    public:
        Blacksmith(sf::Vector2f Position,const sf::Vector2f size = {100.f,100.f});
        virtual ~Blacksmith();

};

#endif // BLACKSMITH_H
