#include <iostream>
#include <memory>

class SubsystemA {
  public:
    std::string operationA() const { return "Subsystem A operation A\n"; }
    std::string operationB() const { return "Subsystem A operation B\n"; }
};

class SubsystemB {
  public:
    std::string operationA() const { return "Subsystem B operation A\n"; }
    std::string operationB() const { return "Subsystem B operation B\n"; }
};

class Facade {
  public:
    Facade(std::unique_ptr<SubsystemA> A, std::unique_ptr<SubsystemB> B)
        : m_subsystemA{std::move(A)}, m_subsystemB{std::move(B)} {}
    std::string operationA() const { return m_subsystemA->operationA() + m_subsystemB->operationA(); }
    std::string operationB() const { return m_subsystemA->operationB() + m_subsystemB->operationB(); }

  private:
    std::unique_ptr<SubsystemA> m_subsystemA;
    std::unique_ptr<SubsystemB> m_subsystemB;
};

int main() {
    auto facade = std::make_unique<Facade>(std::make_unique<SubsystemA>(), std::make_unique<SubsystemB>());
    std::cout << facade->operationA();
    std::cout << facade->operationB();
}
