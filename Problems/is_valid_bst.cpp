#include <cassert>
#include <functional>
#include <iostream>

struct Node {
    int m_value{};
    Node* m_left{nullptr};
    Node* m_right{nullptr};
};

// Helper function to check if a subtree is a valid binary search tree
bool isValidSubtree(Node* root, Node* min, Node* max) {
    // If the root is null, the subtree is valid
    if (!root) {
        return true;
    }
    // If the root's value is less than or equal to the minimum allowed value, the subtree is not valid
    if (min && root->m_value <= min->m_value) {
        return false;
    }
    // If the root's value is greater than or equal to the maximum allowed value, the subtree is not valid
    if (max && root->m_value >= max->m_value) {
        return false;
    }
    // Recursively check if the left and right subtrees are valid binary search trees
    return isValidSubtree(root->m_left, min, root) && isValidSubtree(root->m_right, root, max);
}

// Function to check if a binary tree is a valid binary search tree
bool isValidBST(Node* root) {
    // Call the helper function with the root of the tree and no minimum or maximum allowed values
    return isValidSubtree(root, nullptr, nullptr);
}

int main() {
    // Test case 1: Empty tree
    Node* root1 = nullptr;
    assert(isValidBST(root1) == true);

    // Test case 2: Single node tree
    Node* root2 = new Node{1};
    assert(isValidBST(root2) == true);

    // Test case 3: Valid binary search tree with multiple nodes
    Node* root3 = new Node{2};
    root3->m_left = new Node{1};
    root3->m_right = new Node{3};
    assert(isValidBST(root3) == true);

    // Test case 4: Invalid binary search tree with multiple nodes (left child greater than root)
    Node* root4 = new Node{2};
    root4->m_left = new Node{3};
    root4->m_right = new Node{4};
    assert(isValidBST(root4) == false);

    // Test case 5: Invalid binary search tree with multiple nodes (right child less than root)
    Node* root5 = new Node{3};
    root5->m_left = new Node{2};
    root5->m_right = new Node{1};
    assert(isValidBST(root5) == false);

    // Test case 6: Invalid binary search tree with multiple nodes with the same value
    Node* root6 = new Node{1};
    root6->m_left = new Node{1};
    root6->m_right = new Node{1};
    assert(isValidBST(root6) == false);
}
