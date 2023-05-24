// Time complexity: O(n+k), where n = number of elements, k = range of input. 
// Space complexity: O(k), where k = range of input. 

#include <algorithm>
#include <iostream>
#include <vector>

// Sorts the given data in ascending order using the counting sort algorithm.
void countingSort(std::vector<int>& data) {
    // If the data is empty, there is nothing to sort.
    if (data.empty()) {
        return;
    }

    // Find the maximum value in the data.
    const int maxValue = *std::max_element(data.begin(), data.end());

    // Create a count vector to store the counts of each value in the data.
    std::vector<int> count(maxValue + 1);

    // Count the occurrences of each value in the data.
    for (const int value : data) {
        ++count[value];
    }

    // Update the data vector with the sorted values.
    int index = 0;
    for (int value = 0; value <= maxValue; ++value) {
        while (count[value]-- > 0) {
            data[index++] = value;
        }
    }
}

void print(const std::vector<int>& data) {
    for (const int value : data) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> test1 = {4, 3, 2, 1, 4, 3, 2, 1};
    countingSort(test1);
    print(test1); // 1 1 2 2 3 3 4 4

    std::vector<int> test2 = {1, 2, 3, 4};
    countingSort(test2);
    print(test2); // 1 2 3 4

    std::vector<int> test3 = {4, 3, 2, 1};
    countingSort(test3);
    print(test3); // 1 2 3 4

    std::vector<int> test4 = {1};
    countingSort(test4);
    print(test4); // 1

    std::vector<int> test5 = {};
    countingSort(test5);
    print(test5); //
}
