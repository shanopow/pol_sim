#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class FileReader{
    public:

    std::string filename;
    std::vector<std::vector<std::string>> total_lines;
    FileReader(std::string filename);

    void ReadIn();

    void SentSplit(std::string line, char delimiter);
};

#endif