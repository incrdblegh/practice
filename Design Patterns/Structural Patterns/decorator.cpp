#include <iostream>
#include <memory>
#include <string>

class Beverage {
  public:
    virtual ~Beverage() = default;
    virtual std::string getDescription() = 0;
    virtual int getCost() = 0;
};

class Coffee : public Beverage {
  public:
    std::string getDescription() override { return "coffee"; }
    int getCost() override { return 20; }
};

class Tea : public Beverage {
  public:
    std::string getDescription() override { return "tea"; }
    int getCost() override { return 15; }
};

class Juice : public Beverage {
  public:
    std::string getDescription() override { return "juice"; }
    int getCost() override { return 18; }
};

class Addon : public Beverage {
  public:
    Addon(std::unique_ptr<Beverage> beverage) : m_beverage{std::move(beverage)} {}

  protected:
    std::unique_ptr<Beverage> m_beverage;
};

class Milk : public Addon {
  public:
    using Addon::Addon;
    std::string getDescription() override { return m_beverage->getDescription() + " + milk"; }
    int getCost() override { return m_beverage->getCost() + 7; }
};

class Sugar : public Addon {
  public:
    using Addon::Addon;
    std::string getDescription() override { return m_beverage->getDescription() + " + sugar"; }
    int getCost() override { return m_beverage->getCost() + 3; }
};

class Honey : public Addon {
  public:
    using Addon::Addon;
    std::string getDescription() override { return m_beverage->getDescription() + " + honey"; }
    int getCost() override { return m_beverage->getCost() + 5; }
};

int main() {
    auto beverage = std::make_unique<Honey>(std::make_unique<Milk>(std::make_unique<Tea>()));
    std::cout << beverage->getDescription() << " costs " << beverage->getCost() << " uah\n";
}
