#include <iostream>
#include <memory>
#include <string>

// The Beverage class defines a common interface for beverages.
class Beverage {
  public:
    // Virtual destructor to allow for proper cleanup of derived classes.
    virtual ~Beverage() = default;

    // Pure virtual function to get the description of a beverage.
    [[nodiscard]] virtual std::string getDescription() const = 0;

    // Pure virtual function to get the cost of a beverage.
    [[nodiscard]] virtual int getCost() const = 0;
};

// The Coffee class represents a coffee beverage.
class Coffee : public Beverage {
  public:
    // Returns the description of the coffee beverage.
    std::string getDescription() const override { return "coffee"; }

    // Returns the cost of the coffee beverage.
    int getCost() const override { return 20; }
};

// The Tea class represents a tea beverage.
class Tea : public Beverage {
  public:
    // Returns the description of the tea beverage.
    std::string getDescription() const override { return "tea"; }

    // Returns the cost of the tea beverage.
    int getCost() const override { return 15; }
};

// The Juice class represents a juice beverage.
class Juice : public Beverage {
  public:
    // Returns the description of the juice beverage.
    std::string getDescription() const override { return "juice"; }

    // Returns the cost of the juice beverage.
    int getCost() const override { return 18; }
};

// The Addon class provides a base class for beverage addons.
class Addon : public Beverage {
  public:
    // Constructs an Addon object with the given beverage.
    explicit Addon(std::unique_ptr<Beverage> beverage) : m_beverage{std::move(beverage)} {}

  protected:
    // The decorated beverage.
    std::unique_ptr<Beverage> m_beverage;
};

// The Milk class represents a milk addon for beverages.
class Milk : public Addon {
  public:
    // Inherit the constructors of the base class.
    using Addon::Addon;

    // Returns the description of the beverage with milk added.
    std::string getDescription() const override { return m_beverage->getDescription() + " + milk"; }

    // Returns the cost of the beverage with milk added.
    int getCost() const override { return m_beverage->getCost() + 7; }
};

// The Sugar class represents a sugar addon for beverages.
class Sugar : public Addon {
  public:
    // Inherit the constructors of the base class.
    using Addon::Addon;

    // Returns the description of the beverage with sugar added.
    std::string getDescription() const override { return m_beverage->getDescription() + " + sugar"; }

    // Returns the cost of the beverage with sugar added.
    int getCost() const override { return m_beverage->getCost() + 3; }
};

// The Honey class represents a honey addon for beverages.
class Honey : public Addon {
  public:
    // Inherit the constructors of the base class.
    using Addon::Addon;

    // Returns the description of the beverage with honey added.
    std::string getDescription() const override { return m_beverage->getDescription() + " + honey"; }

    // Returns the cost of the beverage with honey added.
    int getCost() const override { return m_beverage->getCost() + 5; }
};

int main() {
    // Create a tea beverage with milk and honey added.
    const auto beverage = std::make_unique<Honey>(std::make_unique<Milk>(std::make_unique<Tea>()));
    // Print out its description and cost.
    std::cout << beverage->getDescription() << " costs " << beverage->getCost() << " uah\n";
}
