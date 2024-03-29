#include "file_reader.hpp"

// our goal is to make a FileReader for each file, then we can read in all of the possible attribs. 
// With each of these lines, we can now make an object for each line

FileReader::FileReader(std::string filename){
    this->filename = filename;
}

void FileReader::ReadIn(){
    char delimiter = ',';
    std::ifstream fin(this->filename);
    std::string line;

    if (fin.is_open()) {
        // this separates line by line
        bool firstLine = true;
        while (std::getline(fin, line)) {
            // skips processing the first line
            if (firstLine) {
                firstLine = false;
                continue;
            }

            SentSplit(line, delimiter);   
        }
        fin.close();
    }

    else {
        std::cout << "Unable to open file" << "\n";
    }
}

// take a line of the csv file, then separate into a vector of words
void FileReader::SentSplit(std::string line, char delimiter){
    std::istringstream lineStream(line);
    std::string word;
    std::vector<std::string> delim_line;

    while (std::getline(lineStream, word, delimiter)) {
        delim_line.push_back(word);
    }
    this->total_lines.push_back(delim_line);
}


std::shared_ptr<Base> FileReader::createObject(const std::string& type) {
   if (type == "Trait") {
       return std::make_shared<Trait>();
   } else if (type == "Party") {
       return std::make_shared<Party>();
   }
   return nullptr;
}