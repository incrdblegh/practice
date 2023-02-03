// this program implements three types of tree traversal: preorder, inorder, and
// postorder.

#include <iostream>

struct Node {
    int m_data{};
    Node* m_left{nullptr};
    Node* m_right{nullptr};
};

Node* newNode(const int data) {
    Node* temp{new Node{data}};
    return temp;
}

// displaying the node first, then going to the left one, then to the right one
void preorderTraversal(const Node* root) {
    if (root) {
        std::cout << root->m_data << "->";
        preorderTraversal(root->m_left);
        preorderTraversal(root->m_right);
    }
}

// going to the leftmost node first, displaying it, then going to the right one
void inorderTraversal(const Node* root) {
    if (root) {
        inorderTraversal(root->m_left);
        std::cout << root->m_data << "->";
        inorderTraversal(root->m_right);
    }
}

// going to the leftmost node, then to the right one, then displaying it
void postorderTraversal(const Node* root) {
    if (root) {
        postorderTraversal(root->m_left);
        postorderTraversal(root->m_right);
        std::cout << root->m_data << "->";
    }
}

int main() {
    Node* root{newNode(11)};
    root->m_left = newNode(7);
    root->m_right = newNode(5);
    root->m_left->m_left = newNode(13);
    root->m_left->m_right = newNode(19);
    root->m_left->m_left->m_left = newNode(1);
    root->m_right->m_left = newNode(15);
    root->m_right->m_right = newNode(6);
    preorderTraversal(root);
    std::cout << '\n';
    inorderTraversal(root);
    std::cout << '\n';
    postorderTraversal(root);
    std::cout << '\n';
}
