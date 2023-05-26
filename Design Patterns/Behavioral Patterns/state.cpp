// Comments seem redundant for this solution. 

#include <iostream>
#include <memory>
#include <string>

class State {
  public:
    virtual ~State() = default;
    [[nodiscard]] virtual std::string getColor() const = 0;
};

class GreenLight : public State {
  public:
    std::string getColor() const override { return "green light"; }
};

class YellowLight : public State {
  public:
    std::string getColor() const override { return "yellow light"; }
};

class RedLight : public State {
  public:
    std::string getColor() const override { return "red light"; }
};

class Context {
  public:
    virtual ~Context() = default;
    virtual void setState(std::unique_ptr<State> state) = 0;
    virtual void show() const = 0;
};

class TrafficLight : public Context {
  public:
    TrafficLight(std::unique_ptr<State> state) : m_state{std::move(state)} {}
    void setState(std::unique_ptr<State> state) override { m_state = std::move(state); }
    void show() const override { std::cout << m_state->getColor() << '\n'; }

  private:
    std::unique_ptr<State> m_state;
};

void client() {
    auto traffic = std::make_unique<TrafficLight>(std::make_unique<GreenLight>());
    traffic->show();
    traffic->setState(std::make_unique<YellowLight>());
    traffic->show();
    traffic->setState(std::make_unique<RedLight>());
    traffic->show();
}

int main() { client(); }
