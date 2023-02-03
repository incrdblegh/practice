#include <iostream>

struct Node {
    int m_data{};
    Node* m_left{nullptr};
    Node* m_right{nullptr};
};

int getNumOfNodes(const Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return (1 + getNumOfNodes(root->m_left) + getNumOfNodes(root->m_right));
}

bool isCompleteBinaryTree(const Node* root, const int numOfNodes,
                          int index = 0) {
    if (root == nullptr) {
        return true;
    }
    if (index >= numOfNodes) {
        return false;
    }
    return (isCompleteBinaryTree(root->m_left, numOfNodes, 2 * index + 1) &&
            isCompleteBinaryTree(root->m_right, numOfNodes, 2 * index + 2));
}

int main() {
    Node* root{new Node{11}};
    root->m_left = new Node{7};
    root->m_right = new Node{5};
    root->m_left->m_left = new Node{13};
    root->m_right->m_left = new Node{1};
    std::cout << std::boolalpha << "The binary tree is complete: "
              << isCompleteBinaryTree(root, getNumOfNodes(root)) << '\n';
    root->m_left->m_right = new Node{19};
    std::cout << "The binary tree is complete: "
              << isCompleteBinaryTree(root, getNumOfNodes(root)) << '\n';
}
