#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// BulletType represents the intrinsic state of a bullet (its type and damage).
class BulletType {
  public:
    // Constructs a BulletType object with the given type and damage.
    BulletType(const std::string& type, const int damage) : m_type{type}, m_damage{damage} {}

    // Draws this bullet at the given position.
    void draw(int x, int y) const {
        std::cout << m_type << " bullet with " << m_damage << " damage at (" << x << ", " << y << ")\n";
    }

  private:
    // The type of this bullet.
    const std::string m_type;

    // The damage of this bullet.
    const int m_damage;
};

// BulletFactory creates and manages BulletType objects, ensuring that only one
// BulletType object is created for each unique combination of type and damage.
class BulletFactory {
  public:
    // Returns a reference to a BulletType object with the given type and damage.
    const BulletType& getBulletType(const std::string& type, const int damage) {
        auto key = type + std::to_string(damage);
        auto [iterator, _] = m_bulletTypes.try_emplace(key, std::make_unique<BulletType>(type, damage));
        return *(iterator->second);
    }

  private:
    // A map from keys to unique_ptr<BulletType> objects.
    std::unordered_map<std::string, std::unique_ptr<BulletType>> m_bulletTypes;
};

// Bullet represents the extrinsic state of a bullet (its position).
class Bullet {
  public:
    // Constructs a Bullet object with the given position and BulletType.
    Bullet(int x, int y, const BulletType& bulletType) : m_x{x}, m_y{y}, m_bulletType{bulletType} {}

    // Draws this bullet using its associated BulletType object.
    void draw() const { m_bulletType.draw(m_x, m_y); }

  private:
    // The position of this bullet.
    const int m_x;
    const int m_y;

    // The associated BulletType object for this bullet.
    const BulletType& m_bulletType;
};

// A client function that demonstrates how to use the Flyweight pattern to create
// and draw multiple Bullet objects that share the same BulletType objects.
void client() {
    // Create a BulletFactory object to manage BulletType objects.
    const auto factory = std::make_unique<BulletFactory>();

    // Create three Bullet objects that share two different BulletType objects.
    const auto b1 = std::make_unique<Bullet>(5, 6, factory->getBulletType("Standard", 10));
    const auto b2 = std::make_unique<Bullet>(11, 17, factory->getBulletType("Standard", 10));
    const auto b3 = std::make_unique<Bullet>(22, 4, factory->getBulletType("Explosive", 20));
    const auto b4 = std::make_unique<Bullet>(22, 4, factory->getBulletType("Explosive", 20));

    // Draw the bullets on the screen.
    b1->draw();
    b2->draw();
    b3->draw();
    b4->draw();
}

int main() { client(); }
