#include <iostream>
#include <list>
#include <memory>
#include <string>

// Observer interface for receiving updates from a Subject
class Observer {
  public:
    virtual ~Observer() = default;
    // Method called by the Subject to notify the Observer of an update
    virtual void update(const std::string& stock, const float price) = 0;
};

// Subject interface for managing and notifying Observers
class Subject {
  public:
    virtual ~Subject() = default;
    // Register an Observer to receive updates from the Subject
    virtual void registerObserver(std::shared_ptr<Observer> investor) = 0;
    // Remove an Observer from receiving updates from the Subject
    virtual void removeObserver(std::shared_ptr<Observer> investor) = 0;
    // Notify all registered Observers of an update
    virtual void notifyObserver() = 0;
};

// Concrete implementation of the Subject interface representing a stock market
class StockMarket : public Subject {
  public:
    // Register an Observer to receive updates from the StockMarket
    void registerObserver(std::shared_ptr<Observer> investor) override {
        m_investors.emplace_back(std::move(investor));
    }
    // Remove an Observer from receiving updates from the StockMarket
    void removeObserver(std::shared_ptr<Observer> investor) override { m_investors.remove(investor); }
    // Notify all registered Observers of a stock update
    void notifyObserver() override {
        for (const auto& investor : m_investors) {
            investor->update(m_stock, m_price);
        }
    }
    // Update the stock and notify all registered Observers
    void updateStock(const std::string& stock, const float price) {
        m_stock = stock;
        m_price = price;
        notifyObserver();
    }

  private:
    std::string m_stock;                              // The current stock being tracked
    float m_price;                                    // The current price of the stock being tracked
    std::list<std::shared_ptr<Observer>> m_investors; // List of registered Observers
};

// Concrete implementation of the Observer interface representing an investor
class Investor : public Observer {
  public:
    Investor(const int id) : m_id{id} {}
    // Receive a stock update from the StockMarket
    void update(const std::string& stock, const float price) {
        std::cout << "Investor " << m_id << " received stock update: " << stock << ' ' << price << '\n';
    }

  private:
    const int m_id; // Unique identifier for the Investor
};

int main() {
    const auto market = std::make_unique<StockMarket>();
    const auto investor1 = std::make_shared<Investor>(1);
    const auto investor2 = std::make_shared<Investor>(2);
    const auto investor3 = std::make_shared<Investor>(3);
    market->registerObserver(investor1);
    market->registerObserver(investor2);
    market->registerObserver(investor3);
    market->updateStock("someShinyThingy", 420);
}
