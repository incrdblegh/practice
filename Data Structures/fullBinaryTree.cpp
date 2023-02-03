// this program implements a full binary tree data structure.
// the code is (hopefully) self-explanatory.

#include <iostream>

struct Node {
    int m_data{};
    Node* m_left{nullptr};
    Node* m_right{nullptr};
};

bool isFullBinaryTree(const Node* root) {
    if (root->m_left == nullptr && root->m_right == nullptr) {
        return true;
    }
    if (root->m_left != nullptr && root->m_right != nullptr) {
        return (isFullBinaryTree(root->m_left) &&
                isFullBinaryTree(root->m_right));
    }
    return false;
}

int main() {
    Node* root{new Node{11}};
    root->m_left = new Node{7};
    root->m_right = new Node{5};
    root->m_left->m_left = new Node{13};
    root->m_left->m_right = new Node{19};
    root->m_left->m_left->m_left = new Node{1};
    root->m_left->m_left->m_right = new Node{3};
    root->m_right->m_left = new Node{15};
    std::cout << "The binary tree is full: " << std::boolalpha
              << isFullBinaryTree(root) << '\n';
    root->m_right->m_right = new Node{6};
    std::cout << "The binary tree is full: "
              << isFullBinaryTree(root) << '\n';
}
