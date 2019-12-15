#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include"InputKey.h"

class PlayerInput
{
public:
    PlayerInput();
    ~PlayerInput();

    void Update();
    void UpdateKey(InputKey& key);

    InputKey* BindKey(char key);

    ///Binded keys

    std::vector<InputKey*> _keysVector;
};
