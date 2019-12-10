#include "EditorItem.h"

EditorItem::EditorItem(sf::Vector2f size, sf::Color color, size_t id)
    : _id(id), _assignedPlatform(-1), _defaultSize(size)
{
    _itemShape.setSize(_defaultSize);
    _itemShape.setFillColor(color);
}

EditorItem::EditorItem(sf::Vector2f size,const std::string& texturePath, size_t id)
    : _id(id), _assignedPlatform(-1), _defaultSize(size)
{
    _itemShape.setSize(_defaultSize);

    _itemTexture.loadFromFile(texturePath);
    _itemShape.setTexture(&_itemTexture);
}

EditorItem::EditorItem(const EditorItem& item, size_t id)
    : EditorItem(item)
{
    if(id == 0)
        _assignedPlatform = _platformCounter++;
}

void EditorItem::Render(sf::RenderTarget& window)
{
    window.draw(_itemShape);
}

sf::Vector2f EditorItem::getPosition()
{
    return _itemShape.getPosition();
}

void EditorItem::setPosition(sf::Vector2f position)
{
    _itemShape.setPosition(position);
}

void EditorItem::move(sf::Vector2f dist)
{
    _itemShape.move(dist);
}

sf::Vector2f EditorItem::getSize() const
{
    return _itemShape.getSize()*2.f;
}

void EditorItem::setPlatform(int value)
{
    _assignedPlatform = value;
}

int EditorItem::getPlatform()
{
    return _assignedPlatform;
}

sf::FloatRect EditorItem::getGlobalBounds()
{
    return _itemShape.getGlobalBounds();
}

void EditorItem::Enlarge()
{
    switch(_id)
    {
    case 0:
        if(_itemShape.getSize().x < 400.f)
            _itemShape.setSize(_itemShape.getSize() + sf::Vector2f(1.f, 0));
        else
            ResetItem();
        break;
    default:
        break;
    }
}

size_t EditorItem::Id()
{
    return _id;
}

void EditorItem::ResetItem()
{
    _itemShape.setSize(_defaultSize);
}

void EditorItem::ResetPlatformCounter()
{
    _platformCounter = 0;
}

bool EditorItem::IsPlatform() const
{
    return _id == 0;
}

bool EditorItem::IsEnemy() const
{
    if(_id == 1 || _id == 2)
        return true;

    return false;
}

bool EditorItem::IsPlayer() const
{
    return _id == 6;
}

int EditorItem::_platformCounter;
