// this program implements a bubble sort algorithm.

#include <array>
#include <iostream>
#include <utility>

void bubbleSort(std::array<int, 9>& arr) {
    for (std::size_t i{0}; i < arr.size() - 1; ++i) {
        bool isSorted{true};
        for (std::size_t j{0}; j < arr.size() - i - 1; ++j) {
            if (arr.at(j) > arr.at(j + 1)) {
                std::swap(arr.at(j), arr.at(j + 1));
                isSorted = false;
            }
        }
        if (isSorted) {
            std::cout << "Early termination on iteration " << i << '\n';
            return;
        }
    }
}

void printArray(const std::array<int, 9>& arr) {
    for (const auto& element : arr) {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::array<int, 9> arr{6, 3, 2, 9, 7, 1, 5, 4, 8};
    printArray(arr);
    bubbleSort(arr);
    printArray(arr);
}
