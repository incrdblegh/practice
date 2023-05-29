// The code should be self-descriptive for anyone familiar with the Visitor pattern.

#include <iostream>
#include <memory>

class Visitor;

// Abstract element class.
class Shape {
  public:
    virtual ~Shape() = default;
    virtual void applyVisitor(const std::shared_ptr<Visitor> visitor) const = 0;
};

// Concrete element class.
class Rectangle : public Shape {
  public:
    Rectangle(const int width, const int height) : m_width{width}, m_height{height} {}
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    void applyVisitor(const std::shared_ptr<Visitor> visitor) const override;

  private:
    const int m_width{};
    const int m_height{};
};

// Concrete element class.
class Square : public Shape {
  public:
    Square(const int side) : m_side{side} {}
    int getSide() const { return m_side; }
    void applyVisitor(const std::shared_ptr<Visitor> visitor) const override;

  private:
    const int m_side{};
};

// Abstract visitor class.
class Visitor {
  public:
    virtual ~Visitor() = default;
    virtual void visit(const Rectangle* shape) const = 0;
    virtual void visit(const Square* shape) const = 0;
};

// Concrete visitor class.
class ShapeVisitor : public Visitor {
  public:
    void visit(const Rectangle* rectangle) const override {
        std::cout << "The area of the rectangle is: " << rectangle->getHeight() * rectangle->getWidth()
                  << ".\n";
    }
    void visit(const Square* square) const override {
        std::cout << "The area of the square is: " << square->getSide() * square->getSide() << ".\n";
    }
};

void Rectangle::applyVisitor(const std::shared_ptr<Visitor> visitor) const { visitor->visit(this); }
void Square::applyVisitor(const std::shared_ptr<Visitor> visitor) const { visitor->visit(this); }

void client() {
    const auto rectangle = std::make_unique<Rectangle>(5, 8);
    const auto square = std::make_unique<Square>(4);
    const auto visitor = std::make_shared<ShapeVisitor>();
    rectangle->applyVisitor(visitor);
    square->applyVisitor(visitor);
}

int main() { client(); }
