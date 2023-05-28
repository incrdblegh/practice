// Soon to be updated with std::filesystem, as soon as I learn what it is.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// A function to write binary data to a file.
template <typename T> void binaryWrite(const std::string& filename, const std::vector<T>& data) {
    std::ofstream outputFileStream{filename, std::ios::binary};
    // ofstream object will throw on failure.
    outputFileStream.exceptions(std::ios::failbit | std::ios::badbit);
    // write() accepts a pointer to char, hence we reinterpret_cast.
    outputFileStream.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(T));
}

// A function to read binary data from a file.
template <typename T> void binaryRead(const std::string& filename, std::vector<T>& container) {
    std::ifstream inputFileStream{filename, std::ios::binary};
    // ifstream object will throw on failure.
    inputFileStream.exceptions(std::ios::failbit | std::ios::badbit);
    // read() accepts a pointer to char, hence we reinterpret_cast.
    inputFileStream.read(reinterpret_cast<char*>(container.data()), container.size() * sizeof(T));
}

// A simple print function.
template <typename T> void print(const std::vector<T>& container) {
    for (const auto& element : container) {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}

int main() {
    const std::vector data{1, 2, 3, 4, 5};
    const std::string filename{"data.bin"};

    try {
        binaryWrite(filename, data);
    } catch (const std::ios_base::failure& exception) {
        std::cout << exception.what() << '\n';
    }

    std::vector<int> newData(5);

    try {
        binaryRead(filename, newData);
    } catch (const std::ios_base::failure& exception) {
        std::cout << exception.what() << '\n';
    }

    print(newData);
}
