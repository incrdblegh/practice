#include <iostream>
#include <vector>

// print function
void print(const std::vector<int>& sorted) {
    for (auto& a : sorted) {
        std::cout << a << ' ';
    }
    std::cout << '\n';
}

// function to merge divided subarrays
void merge(std::vector<int>& nums, int first, int mid, int last) {
    if (first >= last) {  // check whether indexes are correct
        return;
    }
    int left{first};                   // iterator over left subarray
    int right{mid + 1};                // iterator over right subarray
    int iterator{0};                   // iterator over sorted array
    int size{last - first + 1};        // size of sorted array
    std::vector<int> sorted(size, 0);  // sorted array

    // compare and assign elements of left and right subarrays
    while (left <= mid && right <= last) {
        sorted.at(iterator++) =
            nums.at(left) < nums.at(right) ? nums.at(left++) : nums.at(right++);
    }

    // assign elements from left subarray if right subarray is not valid
    while (left <= mid) {
        sorted.at(iterator++) = nums.at(left++);
    }

    // assign elements from right subarray if left subarray is not valid
    while (right <= last) {
        sorted.at(iterator++) = nums.at(right++);
    }

    // assign sorted array elements to original array
    for (iterator = 0; iterator < size; ++iterator) {
        nums.at(first + iterator) = sorted.at(iterator);
    }
}

// divide and conquer recursive function
void mergeSort(std::vector<int>& nums, int first, int last) {
    if (first >= last) {  // base case
        return;
    }
    int mid{(last - first) / 2 + first};  // calculate  midpoint
    mergeSort(nums, first, mid);          // DaC the left subarray
    mergeSort(nums, mid + 1, last);       // DaC the right subarray
    merge(nums, first, mid, last);        // merge subarrays
}

int main() {
    std::vector<int> nums{7, 5, 3, 8, 2, 1, 4, 9};
    print(nums);
    mergeSort(nums, 0, nums.size() - 1);
    print(nums);
}
