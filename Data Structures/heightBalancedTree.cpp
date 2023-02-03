// this program implements an algorithm to determine whether a tree is
// height-balanced, using DFS traversal. the approach demonstrated in this
// program is considered wasteful due to the use of separate function for height
// calculation. a better approach is presented in the second solution to this
// problem.

#include <algorithm>
#include <cmath>
#include <iostream>

struct Node {
    int m_data{};
    Node* m_left{nullptr};
    Node* m_right{nullptr};
};

int getHeight(const Node* root) {
    // base case, empty node doesn't increase height
    if (root == nullptr) {
        return 0;
    }
    // recursive case, add 1 for each level of height
    return 1 + std::max(getHeight(root->m_left), getHeight(root->m_right));
}

bool isBalanced(const Node* root) {
    // base case, true after reaching the last node
    if (root == nullptr) {
        return true;
    }
    // getting height of each subtree of the current tree
    int leftHeight{getHeight(root->m_left)};
    int rightHeight{getHeight(root->m_right)};

    // tree is balanced if |LH - RH| <= 1 and subtrees are balanced
    return std::abs(leftHeight - rightHeight) <= 1 &&
           isBalanced(root->m_left) && isBalanced(root->m_right);
}

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
