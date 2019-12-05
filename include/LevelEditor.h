#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include"Canvas.h"
#include"Button.h"


class LevelEditor
{
    public:
        LevelEditor(sf::Vector2u size, sf::Font& font);
        virtual ~LevelEditor();

        void Update(const sf::Vector2f& mousePos);
        void Render(sf::RenderTarget& window);

        void Move(sf::Vector2f& distance);

        enum State { open, closed};

        size_t GetState();
        void SetState(size_t state);

    private:

        void initButtons(sf::Font& font);
        void initStrings();
        void initObjects();

        void updateButtons(const sf::Vector2f& mousePos);
        void updateItems(const sf::Vector2f& mousePos);

        void renderItems(sf::RenderTarget& window);

        bool Clicked(const sf::Vector2f& mousePos);
        sf::Vector2f PositionOnMap(const sf::Vector2f& mousePos);
        void AddToFile(size_t id, const sf::Vector2f& position);

        size_t _currentState;
        int _clickedItem;

        Canvas* _editorCanvas;
        Button* _exitButton;

        Canvas* _map;

        std::vector<Button*> _objectsButtonVector;
        std::vector<std::string> _stringsVector;
        std::vector<sf::RectangleShape> _objectsVector;

};

#endif // LEVELEDITOR_H
