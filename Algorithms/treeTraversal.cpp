// this program implements three types of tree traversal: preorder, inorder, and
// postorder. the code is (hopefully) self-explanatory.

#include <iostream>

struct Node {
    int m_data{};
    Node* m_left{nullptr};
    Node* m_right{nullptr};
};

void preorderTraversal(const Node* root) {
    if (root != nullptr) {
        std::cout << root->m_data << "->";
        preorderTraversal(root->m_left);
        preorderTraversal(root->m_right);
    }
}

void inorderTraversal(const Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->m_left);
        std::cout << root->m_data << "->";
        inorderTraversal(root->m_right);
    }
}

void postorderTraversal(const Node* root) {
    if (root != nullptr) {
        postorderTraversal(root->m_left);
        postorderTraversal(root->m_right);
        std::cout << root->m_data << "->";
    }
}

int main() {
    Node* root{new Node{11}};
    root->m_left = new Node{7};
    root->m_right = new Node{5};
    root->m_left->m_left = new Node{13};
    root->m_left->m_right = new Node{19};
    root->m_left->m_left->m_left = new Node{1};
    root->m_right->m_left = new Node{15};
    root->m_right->m_right = new Node{6};
    std::cout << "Preorder traversal: ";
    preorderTraversal(root);
    std::cout << "\nInorder traversal: ";
    inorderTraversal(root);
    std::cout << "\nPostorder traversal: ";
    postorderTraversal(root);
    std::cout << '\n';
}
