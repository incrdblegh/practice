#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Abstract base class representing a node in a tree structure.
class TreeNode {
  public:
    virtual ~TreeNode() = default;

    // Returns a string representation of the tree node.
    virtual std::string print() = 0;
};

// Concrete class representing a leaf node in a tree structure.
class Leaf : public TreeNode {
  public:
    // Returns a string representation of the leaf node.
    std::string print() override { return "leaf"; }
};

// Concrete class representing a composite node in a tree structure.
class Composite : public TreeNode {
  public:
    // Adds the given node as a child of the composite node.
    void addNode(const std::shared_ptr<TreeNode>& node) { m_nodes.push_back(node); }

    // Removes the given node from the children of the composite node.
    void removeNode(const std::shared_ptr<TreeNode>& node) {
        // Use erase-remove idiom to delete the node.
        m_nodes.erase(std::remove(m_nodes.begin(), m_nodes.end(), node), m_nodes.end());
    }

    // Returns a string representation of the composite node and its children.
    std::string print() override {
        std::string result{"composite("};
        for (const auto& node : m_nodes) {
            // Print the closing parentheses if it's the last node.
            if (node != m_nodes.back()) {
                result += node->print() + ", ";
            } else {
                result += node->print() + ")";
            }
        }
        return result;
    }

  private:
    // The child nodes of the composite node.
    std::vector<std::shared_ptr<TreeNode>> m_nodes;
};

int main() {
    // Create a tree structure with two composite nodes and three leaf nodes.
    auto headComposite = std::make_shared<Composite>();
    auto leaf1 = std::make_shared<Leaf>();
    headComposite->addNode(leaf1);
    auto composite1 = std::make_shared<Composite>();
    headComposite->addNode(composite1);
    auto leaf2 = std::make_shared<Leaf>();
    auto leaf3 = std::make_shared<Leaf>();
    composite1->addNode(leaf2);
    composite1->addNode(leaf3);

    // Print the string representation of the tree structure.
    std::cout << headComposite->print();
}
