#include <iostream>
#include <memory>

class LegacyRectangle {
  public:
    void draw(int x1, int y1, int x2, int y2) {
        std::cout << "Top-left corner is (" << x1 << ", " << y1 << ").\nTop-right corner is (" << x2 << ", "
                  << y2 << ").\n";
    }
};

class Shape {
  public:
    virtual void draw(int x, int y, int w, int h) = 0;
};

class RectangleAdaptor : public Shape {
  public:
    RectangleAdaptor(std::unique_ptr<LegacyRectangle> legacy) : m_legacy{std::move(legacy)} {}
    void draw(int x, int y, int w, int h) override { m_legacy->draw(x, y, x + w, y + h); }

  private:
    std::unique_ptr<LegacyRectangle> m_legacy;
};

void client() {
    auto legacy = std::make_unique<LegacyRectangle>();
    auto adaptor = std::make_unique<RectangleAdaptor>(std::move(legacy));
    adaptor->draw(5, 6, 10, 20);
}

int main() { client(); }
