#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

// A function to fill a file with words.
int writeWords(const fs::path& datafile) {
    std::ofstream outputFileStream{datafile};
    if (!outputFileStream) {
        return 1;
    }
    outputFileStream << "hello world something true false random word if else "
                     << "not switch \n yo duds \n something else";
    return 0;
}

// A function to count words in a line.
int countWords(const std::string& line) {
    std::istringstream inputStringStream{line};
    std::string word;
    int count{};
    while (inputStringStream >> word) {
        ++count;
    }
    return count;
}

// A function to read words from a file, count their number, and print the number.
// Certainly doesn't follow the single responsibility principle.
int printNumberOfWords(const fs::path& datafile) {
    std::ifstream inputFileStream{datafile};
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
    const fs::path datafile{"text.txt"};
    
    if (writeWords(datafile)) {
        std::cerr << "Error writing words to the file.\n";
        return 1;
    };
    if (printNumberOfWords(datafile)) {
        std::cerr << "Error reading words from a file.\n";
        return 1;
    };
}
