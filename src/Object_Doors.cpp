#include "Object_Doors.h"

Object_Doors::Object_Doors(sf::Vector2f pos, sf::Vector2f size, size_t scene) : InteractionObject(pos, size)
{
    setTexture("Assets/Images/castledoors.png");

    sceneID = scene;
    areOpen = false;
}

Object_Doors::~Object_Doors()
{

}

void Object_Doors::Interact()
{
    areOpen = true;
}

bool Object_Doors::getOpenStatus()
{
    return areOpen;
}

size_t Object_Doors::getScene()
{
    return sceneID;
}
