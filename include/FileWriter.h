#ifndef FILEWRITER_H
#define FILEWRITER_H

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<SFML/Graphics.hpp>

class FileWriter
{
    public:

        static void AssignFile(size_t mapId, sf::Font& defaultFont);


    private:
        FileWriter() = default;
        virtual ~FileWriter() = default;

        static std::string FileToString(size_t id);

        static std::ofstream _configFile;
        static std::string _path;
        static sf::Font _defaultFont;
};

#endif // FILEWRITER_H
