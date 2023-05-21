#include <iostream>
#include <memory>
#include <string>

class Beverage {
  public:
    virtual ~Beverage() = default;
    [[nodiscard]] virtual std::string getDescription() const = 0;
    [[nodiscard]] virtual int getCost() const = 0;
};

class Coffee : public Beverage {
  public:
    std::string getDescription() const override { return "coffee"; }
    int getCost() const override { return 20; }
};

class Tea : public Beverage {
  public:
    std::string getDescription() const override { return "tea"; }
    int getCost() const override { return 15; }
};

class Juice : public Beverage {
  public:
    std::string getDescription() const override { return "juice"; }
    int getCost() const override { return 18; }
};

class Addon : public Beverage {
  public:
    explicit Addon(std::unique_ptr<Beverage> beverage) : m_beverage{std::move(beverage)} {}

  protected:
    std::unique_ptr<Beverage> m_beverage;
};

class Milk : public Addon {
  public:
    using Addon::Addon;
    std::string getDescription() const override { return m_beverage->getDescription() + " + milk"; }
    int getCost() const override { return m_beverage->getCost() + 7; }
};

class Sugar : public Addon {
  public:
    using Addon::Addon;
    std::string getDescription() const override { return m_beverage->getDescription() + " + sugar"; }
    int getCost() const override { return m_beverage->getCost() + 3; }
};

class Honey : public Addon {
  public:
    using Addon::Addon;
    std::string getDescription() const override { return m_beverage->getDescription() + " + honey"; }
    int getCost() const override { return m_beverage->getCost() + 5; }
};

int main() {
    const auto beverage = std::make_unique<Honey>(std::make_unique<Milk>(std::make_unique<Tea>()));
    std::cout << beverage->getDescription() << " costs " << beverage->getCost() << " uah\n";
}
