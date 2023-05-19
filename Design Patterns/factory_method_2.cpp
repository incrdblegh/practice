#include <iostream>
#include <memory>

class Shape {
  public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Circle : public Shape {
  public:
    void draw() const override { std::cout << "A circle\n"; }
};

class Rectangle : public Shape {
  public:
    void draw() const override { std::cout << "A rectangle\n"; }
};

class Triangle : public Shape {
  public:
    void draw() const override { std::cout << "A triangle\n"; }
};

class ShapeFactory {
  public:
    virtual std::unique_ptr<Shape> createShape() const = 0;
    void operation() const {
        auto newShape = createShape();
        newShape->draw();
    }
};

class CircleShapeFactory : public ShapeFactory {
  public:
    std::unique_ptr<Shape> createShape() const override { return std::make_unique<Circle>(); }
};

class RectangleShapeFactory : public ShapeFactory {
  public:
    std::unique_ptr<Shape> createShape() const override { return std::make_unique<Rectangle>(); }
};

class TriangleShapeFactory : public ShapeFactory {
  public:
    std::unique_ptr<Shape> createShape() const override { return std::make_unique<Triangle>(); }
};

void client(const ShapeFactory& factory) {
    factory.operation();
}

int main() {
    CircleShapeFactory factory1;
    client(factory1);
    RectangleShapeFactory factory2;
    client(factory2);
    TriangleShapeFactory factory3;
    client(factory3);
}
