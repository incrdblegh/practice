// this program implements an algorithm to determine whether a tree is
// height-balanced. unlike the previous solution, this one calculates height
// directly during recursion in the testBalance() function.

#include <algorithm>
#include <cmath>
#include <iostream>

struct Node {
    int m_data{};
    Node* m_left{nullptr};
    Node* m_right{nullptr};
};

int testBalance(const Node* root) {
    // base case, nullptr doesn't count as height
    if (root == nullptr) {
        return 0;
    }
    // recursively calculate height of the left subtree
    int leftHeight{testBalance(root->m_left)};

    // check whether the left subtree is unbalanced
    if (leftHeight == -1) {
        return -1;
    }
    // recursively calculate height of the right subtree
    int rightHeight{testBalance(root->m_right)};

    // check whether the right subtree is unbalanced
    if (rightHeight == -1) {
        return -1;
    }
    // return -1 if subtree is unbalanced
    if (std::abs(leftHeight - rightHeight) > 1) {
        return -1;
    }
    // otherwise return height of the highest subtree with +1 for each level
    return std::max(leftHeight, rightHeight) + 1;
}

// a bool wrapper to interpret int results
bool isBalanced(const Node* root) { return testBalance(root) > 0; }

int main() {
    Node* root{new Node{11}};
    root->m_left = new Node{7};
    root->m_right = new Node{5};
    root->m_left->m_left = new Node{13};
    root->m_left->m_right = new Node{19};
    std::cout << "The tree is height-balanced: " << std::boolalpha
              << isBalanced(root) << '\n';
    root->m_left->m_left->m_left = new Node{1};
    std::cout << "The tree is height-balanced: " << isBalanced(root) << '\n';
}
