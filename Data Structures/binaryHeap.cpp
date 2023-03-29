// this program implements a Binary Heap with the following operations: 
// makeHeap, insert, delete, isHeap, print.

#include <iostream>
#include <utility>
#include <vector>

void print(const std::vector<int>& nums) {
    for (const auto& i : nums) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

void heapify(std::vector<int>& nums, int parent) {
    int size(nums.size());
    int left{parent * 2 + 1};
    int right{parent * 2 + 2};
    int largest{parent};

    // check whether left child is bigger than parent
    if (left < size && nums.at(left) > nums.at(largest)) {
        largest = left;
    }
    // check whether right child is bigger than parent
    if (right < size && nums.at(right) > nums.at(largest)) {
        largest = right;
    }
    // if parent is not the largest, swap and heapify the swapped index
    if (largest != parent) {
        std::swap(nums.at(largest), nums.at(parent));
        heapify(nums, largest);
    }
}

void makeMaxHeap(std::vector<int>& nums) {
    for (int inner(nums.size() / 2 - 1); inner >= 0; --inner) {
        heapify(nums, inner);  // call heapify on each internal node
    }
}

void insert(std::vector<int>& nums, int value) {
    if (nums.empty()) {
        nums.push_back(value);  // push_back if empty
    } else {
        nums.push_back(value);  // push_back if not empty
        makeMaxHeap(nums);      // and heapify
    }
}

void deleteNode(std::vector<int>& nums, int value) {
    int size(nums.size());
    int index{size - 1};  // set index to last in case value is not found

    for (index = 0; index < size; ++index) {  // find the node with value
        if (nums.at(index) == value) {
            break;
        }
    }
    // swap the found node with the last node in heap
    std::swap(nums.at(index), nums.at(size - 1));
    nums.pop_back();    // pop_back the swapped last node
    makeMaxHeap(nums);  // heapify the tree
}

bool isMaxHeap(const std::vector<int>& nums, int node) {
    if (node > nums.size() / 2 - 1) {
        return true;  // return true if current node is leaf node
    }
    int left{node * 2 + 1};
    int right{node * 2 + 2};

    // return true if parent node is bigger than both children nodes,
    // and if each subtree also return true
    if (nums.at(node) >= nums.at(left) && nums.at(node) >= nums.at(right) &&
        isMaxHeap(nums, left) && isMaxHeap(nums, right)) {
        return true;
    };
    return false;  // otherwise return false
}

int main() {
    std::vector<int> nums{5, 7, 3, 1, 9, 8, 4};
    print(nums);
    makeMaxHeap(nums);
    print(nums);
    insert(nums, 6);
    print(nums);
    deleteNode(nums, 9);
    print(nums);
    std::cout << isMaxHeap(nums, 0) << '\n';
}
