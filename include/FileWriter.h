#ifndef FILEWRITER_H
#define FILEWRITER_H

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<SFML/Graphics.hpp>
#include"EditorItem.h"

class FileWriter
{
    public:

        static void AssignFile(size_t mapId, sf::Vector2f (*positionConverter)(const sf::Vector2f&) = nullptr);
        static void WriteData(std::vector<EditorItem*>& itemsVector, std::vector<std::string>& itemsStrings);

    private:
        FileWriter() = default;
        ~FileWriter() = default;

        static std::string FileToString(size_t id);
        static void WriteAdditionalInfo(size_t id);

        static std::ofstream _configFile;
        static std::string _path;

        static sf::Vector2f (*_positionConverter)(const sf::Vector2f&);
};

#endif // FILEWRITER_H
