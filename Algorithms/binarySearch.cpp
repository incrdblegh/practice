// this program implements a binary search algorithm.

#include <array>
#include <iostream>

int binarySearch(const std::array<int, 16>& arr, int search) {
    int min{0};
    int max{static_cast<int>(arr.size() - 1)};

    while (max >= min) {
        int mid{(min + (max - min) / 2)};
        if (arr.at(mid) > search) {
            max = mid - 1;
        } else if (arr.at(mid) < search) {
            min = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int main() {
    std::array arr{1, 2, 4, 7, 8, 9, 13, 15, 17, 23, 25, 27, 33, 37, 40, 42};
    using std::cout;
    cout << "The index of 8 is: " << binarySearch(arr, 8) << '\n';
    cout << "The index of 23 is: " << binarySearch(arr, 23) << '\n';
    cout << "The index of 1 is: " << binarySearch(arr, 1) << '\n';
    cout << "The index of 42 is: " << binarySearch(arr, 42) << '\n';
    cout << "The index of 0 is: " << binarySearch(arr, 0) << '\n';
    cout << "The index of 18 is: " << binarySearch(arr, 18) << '\n';
}
