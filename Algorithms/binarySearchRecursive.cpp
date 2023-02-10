// this program implements a recursive binary search algorithm.

#include <array>
#include <iostream>

int binarySearch(const std::array<int, 15>& arr, int target, int min, int max) {
    if (min > max) {
        return -1;
    }
    int midPoint{(min + max) / 2};

    if (arr.at(midPoint) < target) {
        return binarySearch(arr, target, midPoint + 1, max);
    }
    if (arr.at(midPoint) > target) {
        return binarySearch(arr, target, min, midPoint - 1);
    }
    return midPoint;
}

// the test cases are part of the learncpp curriculum 
int main() {
    using std::array;
    array<int, 15> arr{3, 6, 8, 12, 14, 17, 20, 21, 26, 32, 36, 37, 42, 44, 48};
    constexpr int numTestValues{9};
    array<int, numTestValues> testValues{0, 3, 12, 13, 22, 26, 43, 44, 49};
    array<int, numTestValues> expectedValues{-1, 0, 3, -1, -1, 8, -1, 13, -1};

    for (int count{0}; count < numTestValues; ++count) {
        int index{binarySearch(arr, testValues.at(count), 0, arr.size() - 1)};

        using std::cout;
        if (index == expectedValues.at(count)) {
            cout << "test value " << testValues.at(count) << " passed!\n";
        } else {
            cout << "test value " << testValues.at(count)
                 << " failed.  There's something wrong with your code!\n";
        }
    }
}
