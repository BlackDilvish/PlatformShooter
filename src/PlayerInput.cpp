#include"PlayerInput.h"

PlayerInput::PlayerInput()
{
    _keysVector.push_back(new InputKey(sf::Keyboard::W));
    _keysVector.push_back(new InputKey(sf::Keyboard::D));
    _keysVector.push_back(new InputKey(sf::Keyboard::A));
}

PlayerInput::~PlayerInput()
{
    for(auto key : _keysVector)
        delete key;

    _keysVector.clear();
}

void PlayerInput::UpdateKey(InputKey& key)
{
    if(sf::Keyboard::isKeyPressed(key.KeyCode()))
        {
            if (key.State() == InputKey::KeyState::released)
                key.State(InputKey::KeyState::justPressed);
            else
                key.State(InputKey::KeyState::pressed);
        }
        else
        {
            if (key.State() == InputKey::KeyState::pressed)
                key.State(InputKey::KeyState::justReleased);
            else
                key.State(InputKey::KeyState::released);
        }
}

void PlayerInput::Update()
{
    for(auto key : _keysVector)
        UpdateKey(*key);
}

InputKey* PlayerInput::BindKey(char key)
{
    switch(key)
    {
    case 'w':
        return _keysVector[0];
    case 'd':
        return _keysVector[1];
    case 'a':
        return _keysVector[2];
    default:
        return nullptr;
    }
}
