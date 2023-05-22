#include <iostream>
#include <vector>

// straightforward solution, has the complexity of O(n^2)
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < nums.size(); ++j) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {};
}

// an optimized solution with the complexity of O(n)
// std::vector<int> twoSum(std::vector<int>& nums, int target) {
//     std::unordered_map<int, int> map;
//     for (int i = 0; i < nums.size(); ++i) {
//         int complement = target - nums[i];
//         if (map.count(complement)) {
//             return {map[complement], i};
//         }
//         map[nums[i]] = i;
//     }
//     return {};
// }

int main() {
    std::vector nums{1, 3, 5, 10, 8};
    int target = 8;
    auto result = twoSum(nums, target);
    for (auto& i : result) {
        std::cout << i << ' ';
    }
}
