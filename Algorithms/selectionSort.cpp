// this program implements selection sort algorithm.

#include <algorithm>
#include <array>
#include <iostream>

void printArr(const std::array<int, 10>& arr) {
    for (const int& element : arr) {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}

void selectionSort(std::array<int, 10>& arr) {
    for (std::size_t i{0}; i < arr.size(); ++i) {
        std::size_t smallestIndex{i};
        for (std::size_t j{i}; j < arr.size(); ++j) {
            if (arr[j] < arr[smallestIndex]) {
                smallestIndex = j;
            }
        }
        std::swap(arr[i], arr[smallestIndex]);
        printArr(arr);
    }
}

int main() {
    std::array arr{23, 6, 2, 85, 23, 245, 12, 7, 35, 174};
    printArr(arr);
    selectionSort(arr);
    printArr(arr);
}
