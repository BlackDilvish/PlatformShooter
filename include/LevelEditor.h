#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<sstream>
#include"Canvas.h"
#include"Button.h"
#include"EditorItem.h"
#include"FileWriter.h"


class LevelEditor
{
    public:
        LevelEditor(sf::Vector2u size, sf::Font& font);
        virtual ~LevelEditor();

        enum State { open, closed};

        void Update(const sf::Vector2f& mousePos);
        void Render(sf::RenderTarget& window);

        void Move(sf::Vector2f& distance);
        size_t GetState();
        void SetState(size_t state);

    private:

        ///Private functions

            ///Initializers
        void initCanvases(const sf::Vector2u& size);
        void initStrings();
        void initObjects();
        void initButtons(sf::Font& font);
        void initText(sf::Font& font);

            ///Updates
        void updateButtons(const sf::Vector2f& mousePos);
        void updateItemsButtons(const sf::Vector2f& mousePos);
        void updateItems(const sf::Vector2f& mousePos);
        void updateChosenLevelText();
        void updateTime();

            ///Renderer
        void renderItems(sf::RenderTarget& window);

            ///Clears
        void ClearItems();
        void DeleteItem(size_t id);
        void DeleteButtons();

            ///Adders
        bool ClickedOnMap(const sf::Vector2f& mousePos);
        void CheckIfClickedItem();
        bool IsPlatformBusy(size_t id);
        bool Click();

        void AddToMap(size_t id, const sf::Vector2f& position);
        void SaveInFile();

        ///Private variables

            ///States
        size_t _currentState;
        int _clickedItem;
        size_t _chosenLevel;
        bool _inDeleteMode;

            ///Time
        sf::Clock _clock;
        const float _clickCooldown;
        float _clickTimer;

            ///Canvases
        Canvas* _editorCanvas;
        Canvas* _map;


            ///Buttons
        Button* _saveButton;
        Button* _deleteButton;
        Button* _exitButton;

        Button* _plusMapButton;
        Button* _minusMapButton;
        sf::Text _chosenLevelText;

            ///Vectors
        std::vector<Button*> _itemsButtonVector;
        std::vector<std::string> _stringsVector;
        std::vector<EditorItem*> _itemsVector;

        std::vector<EditorItem*> _addedToMapItemsVector;

};

sf::Vector2f PositionOnMap(const sf::Vector2f& mousePos);

#endif // LEVELEDITOR_H
