#include <iostream>
#include <memory>
#include <unordered_map>

// Abstract base class for shapes
class Shape {
  public:
    // Virtual destructor
    virtual ~Shape() = default;

    // Pure virtual method to clone the shape
    [[nodiscard]] virtual std::unique_ptr<Shape> clone() = 0;

    // Pure virtual method to draw the shape
    virtual void draw() const = 0;
};

// Derived class for circles
class Circle : public Shape {
  public:
    // Override the clone method to create a new instance of Circle
    std::unique_ptr<Shape> clone() override { return std::make_unique<Circle>(*this); }

    // Override the draw method to draw a circle
    void draw() const override { std::cout << "Drawing a circle\n"; }
};

// Derived class for rectangles
class Rectangle : public Shape {
  public:
    // Override the clone method to create a new instance of Rectangle
    std::unique_ptr<Shape> clone() override { return std::make_unique<Rectangle>(*this); }

    // Override the draw method to draw a rectangle
    void draw() const override { std::cout << "Drawing a rectangle\n"; }
};

// Derived class for triangles
class Triangle : public Shape {
  public:
    // Override the clone method to create a new instance of Triangle
    std::unique_ptr<Shape> clone() override { return std::make_unique<Triangle>(*this); }

    // Override the draw method to draw a triangle
    void draw() const override { std::cout << "Drawing a triangle\n"; }
};

// Enum class for shape types
enum class Shapes {
    CIRCLE,
    RECTANGLE,
    TRIANGLE,
};

// Class for managing shape prototypes
class ShapeRegistry final {
  public:
    // Method to add a shape prototype to the registry
    void addShape(const Shapes shape, std::unique_ptr<Shape> prototype) {
        m_registry[shape] = std::move(prototype);
    }

    // Method to clone a shape from the registry
    std::unique_ptr<Shape> cloneShape(const Shapes shape) {
        auto it = m_registry.find(shape);
        if (it != m_registry.end()) {
            return it->second->clone();
        }
        return nullptr;
    }

    // Method to remove a shape prototype from the registry
    void removeShape(const Shapes shape) { m_registry.erase(shape); }

  private:
    // Map to store shape prototypes
    std::unordered_map<Shapes, std::unique_ptr<Shape>> m_registry;
};

// Client code that uses the ShapeRegistry class
void client() {
    auto circle = std::make_unique<Circle>();
    auto registry = std::make_unique<ShapeRegistry>();
    registry->addShape(Shapes::CIRCLE, std::move(circle));
    auto clone = registry->cloneShape(Shapes::CIRCLE);
    registry->removeShape(Shapes::CIRCLE);
    clone->draw();
}

int main() { client(); }
