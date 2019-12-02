#include "Blacksmith.h"

Blacksmith::Blacksmith(sf::Vector2f Position,const sf::Vector2f size) : Npc(Position, size)
{
    setAnimation((char*) "Assets/Images/blacksmithIdle.png", 21, {350.f, 350.f}, 0.04f);

    DefaultInfo("Zwykly chlop, czasem cos sprzedaje");
}

Blacksmith::~Blacksmith()
{
   freeAnimation();
}
