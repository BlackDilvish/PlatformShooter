#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include"Canvas.h"
#include"Button.h"
#include"EditorItem.h"
#include"FileWriter.h"


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

        void ClearItems();

        bool ClickedOnMap(const sf::Vector2f& mousePos);
        void CheckIfClickedItem();
        bool IsPlatformBusy(size_t id);

        void AddToMap(size_t id, const sf::Vector2f& position);
        void SaveInFile();

        ///Variables

        size_t _currentState;
        int _clickedItem;

        Canvas* _editorCanvas;
        Canvas* _map;

        Button* _saveButton;
        Button* _exitButton;

        std::vector<Button*> _itemsButtonVector;
        std::vector<std::string> _stringsVector;
        std::vector<EditorItem*> _itemsVector;

        std::vector<EditorItem*> _addedToMapItemsVector;

};

sf::Vector2f PositionOnMap(const sf::Vector2f& mousePos);

#endif // LEVELEDITOR_H
