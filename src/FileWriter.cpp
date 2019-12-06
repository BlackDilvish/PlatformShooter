#include "FileWriter.h"


void FileWriter::AssignFile(size_t mapId, sf::Font& defaultFont)
{
    _path = FileWriter::FileToString(mapId);
    std::cout<<"Otwieranie: "<<_path<<"\n";
    _defaultFont = defaultFont;
}

std::string FileWriter::FileToString(size_t id)
{
    std::stringstream ss;
    ss<<"Assets/Data/level"<<id<<".txt";

    return ss.str();
}

std::ofstream FileWriter::_configFile;

std::string FileWriter::_path;

sf::Font FileWriter::_defaultFont;
