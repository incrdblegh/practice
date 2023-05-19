#include <iostream>
#include <memory>
#include <unordered_map>

class Shape {
  public:
    virtual ~Shape() = default;
    virtual std::unique_ptr<Shape> clone() = 0;
    virtual void draw() = 0;
};

class Circle : public Shape {
  public:
    std::unique_ptr<Shape> clone() override { return std::make_unique<Circle>(*this); }
    void draw() override { std::cout << "Drawing a circle\n"; }
};

class Rectangle : public Shape {
  public:
    std::unique_ptr<Shape> clone() override { return std::make_unique<Rectangle>(*this); }
    void draw() override { std::cout << "Drawing a rectangle\n"; }
};

class Triangle : public Shape {
  public:
    std::unique_ptr<Shape> clone() override { return std::make_unique<Triangle>(*this); }
    void draw() override { std::cout << "Drawing a triangle\n"; }
};

enum class Shapes {
    CIRCLE,
    RECTANGLE,
    TRIANGLE,
};

class ShapeRegistry final {
  public:
    void addShape(const Shapes shape, std::unique_ptr<Shape> prototype) {
        m_registry[shape] = std::move(prototype);
    }
    std::unique_ptr<Shape> cloneShape(const Shapes shape) {
        if (m_registry[shape]) {
            return m_registry[shape]->clone();
        }
        return nullptr;
    }
    void removeShape(const Shapes shape) { m_registry.erase(shape); }

  private:
    std::unordered_map<Shapes, std::unique_ptr<Shape>> m_registry;
};

void client() {
    auto circle = std::make_unique<Circle>();
    auto registry = std::make_unique<ShapeRegistry>();
    registry->addShape(Shapes::CIRCLE, std::move(circle));
    auto clone = registry->cloneShape(Shapes::CIRCLE);
    clone->draw();
}

int main() { client(); }
