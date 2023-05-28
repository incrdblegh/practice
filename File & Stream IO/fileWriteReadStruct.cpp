// This program makes use of return codes instead of exceptions for the reason of my evening laziness. 

#include <fstream>
#include <iostream>
#include <string>

struct Person {
    std::string m_name;
    int m_age;
};

// A function to write the Person struct to a file.
int writePerson(const std::string& filename, const Person& person) {
    std::ofstream outputFileStream{filename};
    if (!outputFileStream) {
        std::cerr << "Error opening a file.\n";
        return 1;
    }
    outputFileStream << person.m_name << '\n' << person.m_age << '\n';
    return 0;
}

// A functin to read the Person struct from a file.
int readPerson(const std::string& filename, Person& person) {
    std::ifstream inputFileStream{filename};
    if (!inputFileStream) {
        std::cerr << "Error opening a file.\n";
        return 1;
    }
    inputFileStream >> person.m_name >> person.m_age;
    return 0;
}

// A function to delete a file after completing file I/O operations.
int deleteFile(const std::string& filename) {
    if (std::remove(filename.c_str()) != 0) {
        std::cerr << "Error deleting the file.\n";
        return 1;
    } else {
        std::cerr << "File deleted successfully.\n";
        return 0;
    }
}

// A function to print the Person struct.
void printPerson(const Person& person) {
    std::cout << "Name: " << person.m_name << ". Age: " << person.m_age << ".\n";
}

int main() {
    const Person person = {"Alex", 25};
    const std::string filename{"person.txt"};
    writePerson(filename, person);
    Person newPerson;
    readPerson(filename, newPerson);
    printPerson(person);
}
