// this program implements Heap Sort algorithm.

#include <iostream>
#include <utility>
#include <vector>

void print(const std::vector<int>& nums) {
    for (const auto& i : nums) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

void heapify(std::vector<int>& nums, int root, int size) {
    int left{root * 2 + 1};
    int right{root * 2 + 2};
    int largest{root};

    // check whether left child is bigger than root
    if (left < size && nums.at(left) > nums.at(largest)) {
        largest = left;
    }
    // check whether right child is bigger than root
    if (right < size && nums.at(right) > nums.at(largest)) {
        largest = right;
    }
    // if root is not the largest, swap and heapify the swapped index
    if (largest != root) {
        std::swap(nums.at(largest), nums.at(root));
        heapify(nums, largest, size);
    }
}

void makeMaxHeap(std::vector<int>& nums) {
    int size(nums.size());
    for (int inner(size / 2 - 1); inner >= 0; --inner) {
        heapify(nums, inner, size);  // call heapify on each internal node
    }
}

void heapSort(std::vector<int>& nums) {
    int size(nums.size());
    makeMaxHeap(nums);  // make heap before sorting

    // sort by swapping the root node with the last element,
    // and heapifying the array without the swapped element(s)
    for (--size; size >= 0; --size) {
        std::swap(nums.at(0), nums.at(size));
        heapify(nums, 0, size);
    }
}

int main() {
    std::vector<int> nums{5, 7, 3, 1, 9, 8, 4};
    print(nums);
    heapSort(nums);
    print(nums);
}
