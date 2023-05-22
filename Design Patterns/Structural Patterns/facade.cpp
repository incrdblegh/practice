#include <iostream>
#include <memory>

// SubsystemA represents a subsystem that provides two operations: operationA and operationB.
class SubsystemA {
  public:
    // Returns the result of performing operation A on this subsystem.
    [[nodiscard]] std::string operationA() const { return "Subsystem A operation A\n"; }

    // Returns the result of performing operation B on this subsystem.
    [[nodiscard]] std::string operationB() const { return "Subsystem A operation B\n"; }
};

// SubsystemB represents another subsystem that provides two operations: operationA and operationB.
class SubsystemB {
  public:
    // Returns the result of performing operation A on this subsystem.
    [[nodiscard]] std::string operationA() const { return "Subsystem B operation A\n"; }

    // Returns the result of performing operation B on this subsystem.
    [[nodiscard]] std::string operationB() const { return "Subsystem B operation B\n"; }
};

// Facade provides a unified interface to the SubsystemA and SubsystemB subsystems.
class Facade {
  public:
    // Constructs a Facade object that uses the given SubsystemA and SubsystemB objects.
    Facade(std::unique_ptr<SubsystemA> A, std::unique_ptr<SubsystemB> B)
        : m_subsystemA{std::move(A)}, m_subsystemB{std::move(B)} {}

    // Returns the result of performing operation A on both subsystems.
    [[nodiscard]] std::string operationA() const {
        return m_subsystemA->operationA() + m_subsystemB->operationA();
    }

    // Returns the result of performing operation B on both subsystems.
    [[nodiscard]] std::string operationB() const {
        return m_subsystemA->operationB() + m_subsystemB->operationB();
    }

  private:
    // The SubsystemA object used by this Facade object.
    const std::unique_ptr<SubsystemA> m_subsystemA;

    // The SubsystemB object used by this Facade object.
    const std::unique_ptr<SubsystemB> m_subsystemB;
};

int main() {
    // Create a Facade object that uses a SubsystemA object and a SubsystemB object.
    const auto facade =
        std::make_unique<Facade>(std::make_unique<SubsystemA>(), std::make_unique<SubsystemB>());

    // Perform operation A using the Facade object and print the result.
    std::cout << facade->operationA();

    // Perform operation B using the Facade object and print the result.
    std::cout << facade->operationB();
}
