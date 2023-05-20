#include <iostream>
#include <memory>

class Beverage {
  public:
    virtual ~Beverage() = default;
    virtual int getCost() const = 0;
};

class Coffee : public Beverage {
  public:
    int getCost() const override { return 20; }
};

class Addon : public Beverage {
  public:
    Addon(std::unique_ptr<Beverage> beverage) : m_beverage{std::move(beverage)} {}
    int getCost() const override = 0;

  private:
    std::unique_ptr<Beverage> m_beverage;
};

// provide a default definition that can be used in the derived classes
int Addon::getCost() const { return m_beverage->getCost(); }

class Milk : public Addon {
  public:
    using Addon::Addon;
    int getCost() const override { return 5 + Addon::getCost(); }
};

class Sugar : public Addon {
  public:
    using Addon::Addon;
    int getCost() const override { return 1 + Addon::getCost(); }
};

class Cream : public Addon {
  public:
    using Addon::Addon;
    int getCost() const override { return 8 + Addon::getCost(); }
};

int main() {
    auto coffeeWithMilkSugarCream =
        std::make_unique<Cream>(std::make_unique<Sugar>(std::make_unique<Milk>(std::make_unique<Coffee>())));
    std::cout << coffeeWithMilkSugarCream->getCost();
}
