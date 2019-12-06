#include "LevelEditor.h"

LevelEditor::LevelEditor(sf::Vector2u size, sf::Font& font) : _currentState(LevelEditor::closed), _clickedItem(-1)
{
    _editorCanvas = new Canvas(size, sf::Color::Black);
    _map = new Canvas(sf::Vector2u(1750, 720), sf::Color::Blue);

    initStrings();
    initObjects();
    initButtons(font);
}

LevelEditor::~LevelEditor()
{
    delete _editorCanvas;
    delete _map;

    delete _exitButton;
    delete _saveButton;

    for(auto& button : _objectsButtonVector)
        delete button;
}

void LevelEditor::initButtons(sf::Font& font)
{
    _exitButton = new Button({200.f, 100.f}, _editorCanvas->getSize() - sf::Vector2f(200.f, 100.f), font, "Exit", sf::Color::Blue);
    _saveButton = new Button({200.f, 100.f}, _editorCanvas->getSize() - sf::Vector2f(200.f, 100.f + _exitButton->getSize().y*2), font, "Save", sf::Color::Green);

    for(size_t i=0; i<6; i++)
        _objectsButtonVector.push_back(new Button({150.f, 50.f}, sf::Vector2f(200.f*i, _map->getSize().y + 100.f), font, _stringsVector[i], sf::Color(10*i, 10*i, 10*i), sf::Color::White, 20));

}

void LevelEditor::initStrings()
{
    _stringsVector.push_back("Platform");
    _stringsVector.push_back("Enemy(Goblin)");
    _stringsVector.push_back("Enemy(Orc)");
    _stringsVector.push_back("Npc");
    _stringsVector.push_back("Doors");
    _stringsVector.push_back("Coin");
}

void LevelEditor::initObjects()
{
    sf::RectangleShape platformObj(sf::Vector2f(100.f, 50.f));
    platformObj.setFillColor(sf::Color::Green);

    sf::RectangleShape goblinObj(sf::Vector2f(50.f, 50.f));
    goblinObj.setFillColor(sf::Color::Red);

    sf::RectangleShape orcObj(sf::Vector2f(50.f, 50.f));
    orcObj.setFillColor(sf::Color::Red);

    sf::RectangleShape coinObj(sf::Vector2f(25.f, 25.f));
    coinObj.setFillColor(sf::Color::Yellow);

    _objectsVector.push_back(platformObj);
    _objectsVector.push_back(goblinObj);
    _objectsVector.push_back(orcObj);
    _objectsVector.push_back(coinObj);
    _objectsVector.push_back(coinObj);
    _objectsVector.push_back(coinObj);
}

void LevelEditor::updateItems(const sf::Vector2f& mousePos)
{
    if(_clickedItem != -1)
    {
        _objectsVector[_clickedItem].setPosition(mousePos);

        if(ClickedOnMap(mousePos))
            AddToMap(_clickedItem, PositionOnMap(mousePos));
    }

}

void LevelEditor::updateButtons(const sf::Vector2f& mousePos)
{
    if(_exitButton->hovers(mousePos))
    {
        _exitButton->Light();

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _clickedItem = -1;
            _addedToMapObjectsVector.clear();
            _currentState = LevelEditor::closed;
        }
    }
    else if(_saveButton->hovers(mousePos))
    {
        _saveButton->Light();

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            SaveInFile();
    }
    else
    {
        for(size_t i=0; i<_objectsButtonVector.size(); i++)
            if(_objectsButtonVector[i]->hovers(mousePos))
            {
                _objectsButtonVector[i]->Light();

                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    _clickedItem = i;
                }
            }
            else
                _objectsButtonVector[i]->Dark();

        _exitButton->Dark();
        _saveButton->Dark();
    }
}

void LevelEditor::Update(const sf::Vector2f& mousePos)
{
    switch(_currentState)
    {
    case LevelEditor::open:
        updateButtons(mousePos);
        updateItems(mousePos);
        break;
    case LevelEditor::closed:
        break;
    default:
        break;
    }
}

void LevelEditor::renderItems(sf::RenderTarget& window)
{
    if(_clickedItem != -1)
        window.draw(_objectsVector[_clickedItem]);
}

void LevelEditor::Render(sf::RenderTarget& window)
{
    _editorCanvas->render(window);
    _map->render(window);

    _exitButton->render(window);
    _saveButton->render(window);

    for(auto& button : _objectsButtonVector)
        button->render(window);

    for(auto& icon : _addedToMapObjectsVector)
        window.draw(icon);

    renderItems(window);
}

void LevelEditor::Move(sf::Vector2f& distance)
{
    _editorCanvas->move(distance);
    _map->move(distance);

    _exitButton->move(distance);
    _saveButton->move(distance);

    for(auto& button : _objectsButtonVector)
        button->move(distance);

    for(auto& icon : _addedToMapObjectsVector)
        icon.move(distance);
}

size_t LevelEditor::GetState()
{
    return _currentState;
}

void LevelEditor::SetState(size_t state)
{
    _currentState = state;
}

sf::Vector2f LevelEditor::PositionOnMap(const sf::Vector2f& mousePos)
{
    return (mousePos - sf::Vector2f(0, 180.f)) * 2.f;
}

bool LevelEditor::ClickedOnMap(const sf::Vector2f& mousePos)
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left) && _map->getGlobalBounds().contains(mousePos);
}

void LevelEditor::AddToMap(size_t id, const sf::Vector2f& position)
{
    std::cout<<"ID: "<<id<<" x: "<<position.x<<" y: "<<position.y<<"\n";

    _addedToMapObjectsVector.push_back(sf::RectangleShape(_objectsVector[id]));
    _clickedItem = -1;
}

void LevelEditor::SaveInFile()
{
    ///saving via FileWriter

    _addedToMapObjectsVector.clear();
}
