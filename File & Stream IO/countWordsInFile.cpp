// The error handling in this program is somewhat lacking, but will do for now. 

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int writeWords(const std::string& filename) {
    std::ofstream outputFileStream{filename};
    if (!outputFileStream) {
        return 1;
    }
    outputFileStream << "hello world something true false random word if else "
                     << "not switch \n yo duds \n something else";
    return 0;
}

int countWords(const std::string& line) {
    std::istringstream inputStringStream{line};
    std::string word;
    int count{};
    while (inputStringStream >> word) {
        ++count;
    }
    return count;
}

int printNumberOfWords(const std::string& filename) {
    std::ifstream inputFileStream{filename};
    if (!inputFileStream) {
        return 1;
    }
    std::string line;
    int wordCount{};
    while (std::getline(inputFileStream, line)) {
        wordCount += countWords(line);
    }
    std::cout << "Number of words: " << wordCount << '\n';
    return 0;
}

int main() {
    const std::string filename{"text.txt"};

    if (writeWords(filename) != 0) {
        std::cerr << "Error writing words to the file.\n";
        return 1;
    };

    if (printNumberOfWords(filename) != 0) {
        std::cerr << "Error reading words from a file.\n";
        return 1;
    };
}
