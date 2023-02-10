// this program implements a perfect binary tree data structure.

#include <iostream>

struct Node {
    int m_data{};
    Node* m_left{nullptr};
    Node* m_right{nullptr};
};

int getDepth(const Node* root) {
    int depth{0};
    while (root->m_left != nullptr) {
        root = root->m_left;
        ++depth;
    }
    return depth;
}

bool isPerfectBinaryTree(const Node* root, int depth, int level = 0) {
    if (root->m_left == nullptr && root->m_right == nullptr && level == depth) {
        return true;
    }
    if (root->m_left != nullptr && root->m_right != nullptr) {
        return (isPerfectBinaryTree(root->m_left, depth, level + 1) &&
                isPerfectBinaryTree(root->m_right, depth, level + 1));
    }
    return false;
}

int main() {
    Node* root{new Node{11}};
    root->m_left = new Node{7};
    root->m_right = new Node{5};
    root->m_left->m_left = new Node{13};
    root->m_left->m_right = new Node{19};
    root->m_right->m_left = new Node{1};
    std::cout << "A perfect binary tree: " << std::boolalpha
              << isPerfectBinaryTree(root, getDepth(root)) << '\n';
    root->m_right->m_right = new Node{3};
    std::cout << "A perfect binary tree: "
              << isPerfectBinaryTree(root, getDepth(root)) << '\n';
}
