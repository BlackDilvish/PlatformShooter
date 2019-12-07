#include "FileWriter.h"


void FileWriter::AssignFile(size_t mapId, sf::Vector2f (*positionConverter)(const sf::Vector2f&))
{
    _path = FileWriter::FileToString(mapId);
    std::cout<<"Otwieranie: "<<_path<<"\n";

    _positionConverter = positionConverter;
}

void FileWriter::WriteData(std::vector<EditorItem*>& itemsVector, std::vector<std::string>& itemsStrings)
{
    _configFile.open(_path);

    _configFile<<"mapSize: 3500 -360 "<<"\n\n";

    for(auto& item : itemsVector)
    {
        sf::Vector2f position;

        if(_positionConverter)
            position = _positionConverter(item->getPosition());
        else
            position = item->getPosition();

        if(item->getPlatform() >= 0 &&
            (item->Id() == 1 || item->Id() == 2))
        {
            _configFile<<itemsStrings[item->Id()]<<"(Platform): "<<item->getPlatform()<<"\n";
        }
        else
        {
            _configFile<<itemsStrings[item->Id()]<<": "<<
                         position.x<<" "<<position.y<<" "<<
                         item->getSize().x<<" "<<item->getSize().y;

            WriteAdditionalInfo(item->Id());
        }


    }

    _configFile.close();
}

std::string FileWriter::FileToString(size_t id)
{
    std::stringstream ss;
    ss<<"Assets/Data/level"<<id<<".txt";

    return ss.str();
}

void FileWriter::WriteAdditionalInfo(size_t id)
{
    switch(id)
        {
        case 0:
            _configFile<<" *insert platform type*\n";
            break;
        case 1:
            _configFile<<" *insert Enemy range*\n";
            break;
        case 2:
            _configFile<<" *insert Enemy range*\n";
            break;
        case 3:
            _configFile<<" *insert number of dialogs and dialog itself*\n";
            break;
        case 4:
            _configFile<<" *insert scene id*\n";
            break;
        case 5:
            _configFile<<" 0\n";
            break;
        default:
            break;
        }
}

std::ofstream FileWriter::_configFile;

std::string FileWriter::_path;

sf::Vector2f (*FileWriter::_positionConverter)(const sf::Vector2f&);
