#ifndef OBJECT_DOORS_H
#define OBJECT_DOORS_H

#include"InteractionObject.h"

class Object_Doors : public InteractionObject
{
    public:
        Object_Doors(sf::Vector2f pos, sf::Vector2f size, size_t scene);
        virtual ~Object_Doors();

        bool getOpenStatus();
        size_t getScene();
    protected:

    private:
        void Interact(const Player &player);

        bool areOpen;
        size_t sceneID;
};

#endif // OBJECT_DOORS_H
