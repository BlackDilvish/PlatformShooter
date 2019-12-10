#include "LevelEditor.h"

LevelEditor::LevelEditor(sf::Vector2u size, sf::Font& font)
    : _currentState(LevelEditor::closed), _clickedItem(-1), _chosenLevel(3), _inDeleteMode(false), _clickCooldown(0.3f), _clickTimer(0)
{
    initCanvases(size);
    initStrings();
    initObjects();
    initButtons(font);
    initText(font);
}

LevelEditor::~LevelEditor()
{
    delete _editorCanvas;
    delete _map;

    DeleteButtons();

    for(auto& item : _itemsVector)
        delete item;
    _itemsVector.clear();

    ClearItems();
}

void LevelEditor::initCanvases(const sf::Vector2u& size)
{
    _editorCanvas = new Canvas(size, sf::Color::Black);
    _map = new Canvas(sf::Vector2u(1750, 720), "Assets/Images/forest1Background.png");
}

void LevelEditor::initButtons(sf::Font& font)
{
    _exitButton = new Button({200.f, 100.f}, _editorCanvas->getSize() - sf::Vector2f(200.f, 100.f), font, "Exit", sf::Color::Blue);
    _deleteButton = new Button({200.f, 100.f}, _editorCanvas->getSize() - sf::Vector2f(200.f, 100.f + _exitButton->getSize().y*1.2f), font, "Delete", sf::Color::Cyan);
    _saveButton = new Button({200.f, 100.f}, _editorCanvas->getSize() - sf::Vector2f(200.f, 100.f + _exitButton->getSize().y*2.4f), font, "Save", sf::Color::Green);

    _plusMapButton = new Button({100.f, 100.f}, _saveButton->getPosition() - sf::Vector2f(200.f, 0), font, "+", sf::Color::Green);
    _minusMapButton = new Button({100.f, 100.f}, _saveButton->getPosition() - sf::Vector2f(400.f, 0), font, "-", sf::Color::Red);

    for(size_t i=0; i<6; i++)
        _itemsButtonVector.push_back(new Button({150.f, 50.f}, sf::Vector2f(200.f*i, _map->getSize().y + 100.f), font, _stringsVector[i], sf::Color::Yellow, sf::Color(163, 95, 23), 20));
    for(size_t i=6; i<7; i++)
        _itemsButtonVector.push_back(new Button({150.f, 50.f}, sf::Vector2f(200.f*(i-6), _map->getSize().y + 200.f), font, _stringsVector[i], sf::Color::Yellow, sf::Color(163, 95, 23), 20));

}

void LevelEditor::initText(sf::Font& font)
{
    _chosenLevelText.setFont(font);
    _chosenLevelText.setPosition(_minusMapButton->getPosition() + sf::Vector2f(100.f, 0));
    _chosenLevelText.setCharacterSize(64);

    updateChosenLevelText();
}

void LevelEditor::initStrings()
{
    _stringsVector.push_back("Platform");
    _stringsVector.push_back("Goblin");
    _stringsVector.push_back("Orc");
    _stringsVector.push_back("BlackSmith");
    _stringsVector.push_back("Doors");
    _stringsVector.push_back("Coin");
    _stringsVector.push_back("PlayerPosition");
}

void LevelEditor::initObjects()
{
    _itemsVector.push_back(new EditorItem(sf::Vector2f(100.f, 50.f), "Assets/Images/Items/ItemPlatform.png",   0));
    _itemsVector.push_back(new EditorItem(sf::Vector2f(50.f, 50.f),  "Assets/Images/Items/ItemGoblin.png",     1));
    _itemsVector.push_back(new EditorItem(sf::Vector2f(50.f, 50.f),  "Assets/Images/Items/ItemOrc.png",        2));
    _itemsVector.push_back(new EditorItem(sf::Vector2f(50.f, 50.f),  "Assets/Images/Items/ItemBlackSmith.png", 3));
    _itemsVector.push_back(new EditorItem(sf::Vector2f(40.f, 50.f),  "Assets/Images/Items/ItemDoors.png",      4));
    _itemsVector.push_back(new EditorItem(sf::Vector2f(20.f, 20.f),  "Assets/Images/Items/ItemCoin.png",       5));
    _itemsVector.push_back(new EditorItem(sf::Vector2f(50.f, 50.f),  "Assets/Images/Items/ItemPlayer.png",     6));
}

void LevelEditor::updateItems(const sf::Vector2f& mousePos)
{
    if(_clickedItem != -1)
    {
        _itemsVector[_clickedItem]->setPosition(mousePos);

        if(ClickedOnMap(mousePos))
            AddToMap(_clickedItem, PositionOnMap(mousePos));

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            _itemsVector[_clickedItem]->Enlarge();
    }

    if(_inDeleteMode)
        for(size_t i=0; i<_addedToMapItemsVector.size(); i++)
            if(_addedToMapItemsVector[i]->getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                DeleteItem(i);

}

void LevelEditor::updateButtons(const sf::Vector2f& mousePos)
{
    if(_exitButton->hovers(mousePos))
    {
        _exitButton->Light();

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _clickedItem = -1;
            ClearItems();
            _currentState = LevelEditor::closed;
        }
    }
    else if(_deleteButton->hovers(mousePos))
    {
        _deleteButton->Light();

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && _clickedItem != -2)
            _inDeleteMode = true;

    }
    else if(_saveButton->hovers(mousePos))
    {
        _saveButton->Light();

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            SaveInFile();
    }
    else if(_plusMapButton->hovers(mousePos))
    {
        _plusMapButton->Light();

        if(Click())
        {
            _chosenLevel++;
            updateChosenLevelText();
        }
    }
    else if(_minusMapButton->hovers(mousePos))
    {
        _minusMapButton->Light();

        if(Click() && _chosenLevel > 0)
        {
            _chosenLevel--;
            updateChosenLevelText();
        }
    }
    else
    {
        updateItemsButtons(mousePos);

        _exitButton->Dark();
        _deleteButton->Dark();
        _saveButton->Dark();

        _plusMapButton->Dark();
        _minusMapButton->Dark();
    }
}

void LevelEditor::updateItemsButtons(const sf::Vector2f& mousePos)
{
    for(size_t i=0; i<_itemsButtonVector.size(); i++)
        if(_itemsButtonVector[i]->hovers(mousePos))
        {
            _itemsButtonVector[i]->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                _clickedItem = i;
                _inDeleteMode = false;
            }
        }
        else
            _itemsButtonVector[i]->Dark();
}

void LevelEditor::updateChosenLevelText()
{
    std::stringstream ss;
    ss<<_chosenLevel;

    _chosenLevelText.setString(ss.str());
}

void LevelEditor::updateTime()
{
    if(_clickTimer < _clickCooldown)
        _clickTimer += _clock.getElapsedTime().asSeconds();

    _clock.restart().asSeconds();
}

void LevelEditor::Update(const sf::Vector2f& mousePos)
{
    switch(_currentState)
    {
    case LevelEditor::open:
        updateButtons(mousePos);
        updateItems(mousePos);
        updateTime();
        break;
    case LevelEditor::closed:
        break;
    default:
        break;
    }
}

void LevelEditor::renderItems(sf::RenderTarget& window)
{
    for(auto& icon : _addedToMapItemsVector)
        icon->Render(window);

    if(_clickedItem != -1)
        _itemsVector[_clickedItem]->Render(window);
}

void LevelEditor::Render(sf::RenderTarget& window)
{
    _editorCanvas->render(window);
    _map->render(window);

    _exitButton->render(window);
    _deleteButton->render(window);
    _saveButton->render(window);

    _plusMapButton->render(window);
    _minusMapButton->render(window);
    window.draw(_chosenLevelText);

    for(auto& button : _itemsButtonVector)
        button->render(window);

    renderItems(window);
}

void LevelEditor::ClearItems()
{
    for(auto& item : _addedToMapItemsVector)
        delete item;

    _addedToMapItemsVector.clear();
    EditorItem::ResetPlatformCounter();
}

void LevelEditor::DeleteItem(size_t id)
{
    delete _addedToMapItemsVector[id];
    _addedToMapItemsVector.erase(_addedToMapItemsVector.begin() + id);
}

void LevelEditor::DeleteButtons()
{
    delete _exitButton;
    delete _deleteButton;
    delete _saveButton;

    delete _plusMapButton;
    delete _minusMapButton;

    for(auto& button : _itemsButtonVector)
        delete button;
}

void LevelEditor::Move(sf::Vector2f& distance)
{
    _editorCanvas->move(distance);
    _map->move(distance);

    _exitButton->move(distance);
    _deleteButton->move(distance);
    _saveButton->move(distance);

    _plusMapButton->move(distance);
    _minusMapButton->move(distance);
    _chosenLevelText.move(distance);

    for(auto& button : _itemsButtonVector)
        button->move(distance);

    for(auto& icon : _addedToMapItemsVector)
        icon->move(distance);
}

size_t LevelEditor::GetState()
{
    return _currentState;
}

void LevelEditor::SetState(size_t state)
{
    _currentState = state;
}

sf::Vector2f PositionOnMap(const sf::Vector2f& mousePos)
{
    return (mousePos - sf::Vector2f(0, 180.f)) * 2.f;
}

bool LevelEditor::ClickedOnMap(const sf::Vector2f& mousePos)
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left) && _map->getGlobalBounds().contains(mousePos);
}

bool LevelEditor::Click()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && _clickTimer > _clickCooldown)
    {
        _clickTimer = 0;
        return true;
    }

    return false;
}

void LevelEditor::CheckIfClickedItem()
{
    for(size_t i=0; i<_addedToMapItemsVector.size() - 1; i++)
    {
        if(_addedToMapItemsVector[i]->getGlobalBounds().intersects(_addedToMapItemsVector[_addedToMapItemsVector.size()-1]->getGlobalBounds()))
        {
            if(_addedToMapItemsVector[i]->IsPlatform() && !IsPlatformBusy(i) &&
               _addedToMapItemsVector[_addedToMapItemsVector.size() - 1]->IsEnemy() )
            {
                _addedToMapItemsVector[_addedToMapItemsVector.size() - 1]->setPlatform(_addedToMapItemsVector[i]->getPlatform());
                _addedToMapItemsVector[_addedToMapItemsVector.size() - 1]->setPosition(_addedToMapItemsVector[i]->getPosition() - sf::Vector2f(0, _addedToMapItemsVector[i]->getSize().y)/2.f);
            }
            else
            {
                delete _addedToMapItemsVector[_addedToMapItemsVector.size()-1];
                _addedToMapItemsVector.erase(_addedToMapItemsVector.begin() + _addedToMapItemsVector.size() - 1);
            }

        }
    }
}

bool LevelEditor::IsPlatformBusy(size_t i)
{
    for(size_t j=0; j<_addedToMapItemsVector.size() - 1; j++)
        if(_addedToMapItemsVector[j]->IsEnemy() && _addedToMapItemsVector[j]->getPlatform() == _addedToMapItemsVector[i]->getPlatform() )
            return true;

    return false;
}

void LevelEditor::AddToMap(size_t id, const sf::Vector2f& position)
{
    _addedToMapItemsVector.push_back(new EditorItem(*_itemsVector[id], id));

    CheckIfClickedItem();

    _itemsVector[_clickedItem]->ResetItem();
    _clickedItem = -1;
}

void LevelEditor::SaveInFile()
{
    if(_addedToMapItemsVector.size() == 0)
        return;

    FileWriter::AssignFile(_chosenLevel, &PositionOnMap);
    FileWriter::WriteData(_addedToMapItemsVector, _stringsVector);

    ClearItems();
}
