#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

struct Person {
    std::string m_name;
    int m_age;
};

// A function to write the Person struct to a file.
int writePerson(const fs::path& datafile, const Person& person) {
    std::ofstream outputFileStream{datafile};
    if (!outputFileStream) {
        std::cerr << "Error opening a file.\n";
        return 1;
    }
    outputFileStream << person.m_name << '\n' << person.m_age << '\n';
    return 0;
}

// A functin to read the Person struct from a file.
int readPerson(const fs::path& datafile, Person& person) {
    std::ifstream inputFileStream{datafile};
    if (!inputFileStream) {
        std::cerr << "Error opening a file.\n";
        return 1;
    }
    inputFileStream >> person.m_name >> person.m_age;
    return 0;
}

// A function to delete a file after completing file I/O operations.
int deleteFile(const fs::path& datafile) {
    if (fs::remove(datafile)) {
        std::cout << "File deleted successfully.\n";
        return 0;
    } else {
        std::cerr << "Error deleting the file.\n";
        return 1;
    }
}

// A function to print the Person struct.
void printPerson(const Person& person) {
    std::cout << "Name: " << person.m_name << ". Age: " << person.m_age << ".\n";
}

int main() {
    const Person person = {"Garrison", 34};
    const fs::path datafile{"person.txt"};

    if (writePerson(datafile, person) != 0) {
        return 1;
    }

    Person newPerson;

    if (readPerson(datafile, newPerson) != 0) {
        return 1;
    }

    printPerson(person);

    if (deleteFile(datafile) != 0) {
        return 1;
    }
}
