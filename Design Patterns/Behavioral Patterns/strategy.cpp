#include <iostream>
#include <memory>

// Strategy interface.
class Strategy {
  public:
    virtual ~Strategy() = default;
    [[nodiscard]] virtual int operation(int a, int b) const = 0;
};

// Concrete Strategy.
class Add : public Strategy {
  public:
    int operation(int a, int b) const override { return a + b; }
};

// Concrete Strategy.
class Sub : public Strategy {
  public:
    int operation(int a, int b) const override { return a - b; }
};

// Context class.
class Calculator {
  public:
    Calculator(std::unique_ptr<Strategy> strategy) : m_strategy{std::move(strategy)} {}
    int operation(int a, int b) const { return m_strategy->operation(a, b); }
    void setStrategy(std::unique_ptr<Strategy> strategy) { m_strategy = std::move(strategy); }

  private:
    std::unique_ptr<Strategy> m_strategy;
};

void client() {
    auto calculator = std::make_unique<Calculator>(std::make_unique<Add>());
    std::cout << calculator->operation(35, 74) << '\n';
    calculator->setStrategy(std::make_unique<Sub>());
    std::cout << calculator->operation(72, 57) << '\n';
}

int main() { client(); }
