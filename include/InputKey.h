#include<iostream>
#include<SFML/Graphics.hpp>


class InputKey
{

public:
    InputKey(sf::Keyboard::Key code)
    {
        _keyCode = code;
        _keyState = KeyState::released;
    }

    enum KeyState { pressed, released, justPressed, justReleased};

    sf::Keyboard::Key KeyCode() const { return _keyCode; }
    void KeyCode(sf::Keyboard::Key code) { _keyCode = code; }

    KeyState State() const { return _keyState; }
    void State(KeyState state) { _keyState = state; }

private:
    sf::Keyboard::Key _keyCode;
    KeyState          _keyState;
};
