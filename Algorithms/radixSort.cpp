// Time complexity: O(k*n), where k = max length of a string, n = number of strings.
// Space complexity: O(k+n), where k = max length of a string, n = number of strings.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Sorts a vector of strings in lexicographic order using counting sort.
void countingSort(std::vector<std::string>& strings, int index) {
    // Create a vector to store the frequency of each character. 26 for a-z, 27th for an empty character.
    std::vector<int> charCount(27);

    // Count the frequency of each character in the strings.
    for (const auto& string : strings) {
        int charIndex = string.size() > index ? string[index] - 'a' + 1 : 0;
        charCount[charIndex]++;
    }
    // Calculate the cumulative sum of the count vector.
    for (int i = 1; i < charCount.size(); ++i) {
        charCount[i] += charCount[i - 1];
    }
    // Create a vector to store the sorted strings.
    std::vector<std::string> sortedStrings(strings.size());

    // Place the strings in their sorted position in the sorted vector.
    for (int i = strings.size() - 1; i >= 0; --i) {
        int charIndex = strings[i].size() > index ? strings[i][index] - 'a' + 1 : 0;
        sortedStrings[--charCount[charIndex]] = strings[i];
    }
    // Update the input vector with the sorted strings.
    strings = std::move(sortedStrings);
}

// Sorts a vector of strings in lexicographic order using radix sort.
void radixSort(std::vector<std::string>& strings) {
    // Find the maximum length of the strings.
    int maxLength = 0;
    for (const auto& string : strings) {
        maxLength = std::max(maxLength, static_cast<int>(string.size()));
    }
    // Perform counting sort on each character position from right to left.
    for (int i = maxLength - 1; i >= 0; --i) {
        countingSort(strings, i);
    }
}

int main() {
    std::vector<std::string> test1 = {"hello", "world", "apple", "banana", "cat", "dog"};
    radixSort(test1);
    for (const auto& str : test1) {
        std::cout << str << ' ';
    }
    std::cout << '\n';

    std::vector<std::string> test2 = {"zebra", "apple", "banana", "cat", "dog"};
    radixSort(test2);
    for (const auto& str : test2) {
        std::cout << str << ' ';
    }
    std::cout << '\n';

    std::vector<std::string> test3 = {"cat", "dog", "mouse", "elephant", "tiger"};
    radixSort(test3);
    for (const auto& str : test3) {
        std::cout << str << ' ';
    }
    std::cout << '\n';

    std::vector<std::string> test4 = {"abcd", "abc", "abcde", "ab", "abcdef"};
    radixSort(test4);
    for (const auto& str : test4) {
        std::cout << str << ' ';
    }
    std::cout << '\n';

    std::vector<std::string> test5 = {"aaa", "aa", "aaaaa", "a", "aaaa"};
    radixSort(test5);
    for (const auto& str : test5) {
        std::cout << str << ' ';
    }
    std::cout << '\n';
}
