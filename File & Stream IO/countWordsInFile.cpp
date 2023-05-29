// The error handling in this program is somewhat lacking, but will do for now.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// A function to fill a file with words.
int writeWords(const std::string& filename) {
    std::ofstream outputFileStream{filename};
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
    
    if (writeWords(filename)) {
        std::cerr << "Error writing words to the file.\n";
        return 1;
    };
    if (printNumberOfWords(filename)) {
        std::cerr << "Error reading words from a file.\n";
        return 1;
    };
}
