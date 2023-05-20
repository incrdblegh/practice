#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Component {
  public:
    virtual ~Component() = default;
    virtual std::string operation() = 0;
};

class Leaf : public Component {
  public:
    std::string operation() override { return "leaf"; }
};

class Composite : public Component {
  public:
    void addNode(const std::shared_ptr<Component>& node) { m_components.push_back(node); }
    void removeNode(const std::shared_ptr<Component>& node) {
      // use erase-remove idiom to delete the node
        m_components.erase(std::remove(m_components.begin(), m_components.end(), node), m_components.end());
    }
    std::string operation() override {
        std::string result{"composite("};
        for (const auto& node : m_components) {
          // print a closing parentheses instead of a comma if it's the last component
            if (node != m_components.back()) {
                result += node->operation() + ", ";
            } else {
                result += node->operation() + ")";
            }
        }
        return result;
    }

  private:
    std::vector<std::shared_ptr<Component>> m_components;
};

int main() {
    auto headComposite = std::make_shared<Composite>();
    auto leaf1 = std::make_shared<Leaf>();
    headComposite->addNode(leaf1);
    auto composite1 = std::make_shared<Composite>();
    headComposite->addNode(composite1);
    auto leaf2 = std::make_shared<Leaf>();
    auto leaf3 = std::make_shared<Leaf>();
    composite1->addNode(leaf2);
    composite1->addNode(leaf3);
    std::cout << headComposite->operation();
}
