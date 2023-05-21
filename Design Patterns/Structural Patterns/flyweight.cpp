#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// intrinsic (constant) part of the bullet
class BulletType {
  public:
    BulletType(const std::string& type, const int damage) : m_type{type}, m_damage{damage} {}
    void draw(int x, int y) const {
        std::cout << m_type << " bullet with " << m_damage << " damage at (" << x << ", " << y << ")\n";
    }

  private:
    const std::string m_type;
    const int m_damage;
};

// factory keeps track of the existing intrinsic parts of the bullet, and provides access to them
class BulletFactory {
  public:
    const BulletType& getBulletType(const std::string& type, const int damage) {
        // type and damage are used to create a unique key in the map. use a structured binding to give a name
        // to the iterator returned by try_emplace, and use a placeholder to ignore the boolean value
        auto [iterator, _] = m_bulletTypes.try_emplace(type + std::to_string(damage),
                                                       std::make_unique<BulletType>(type, damage));
        return *(iterator->second);
    }

  private:
    std::unordered_map<std::string, std::unique_ptr<BulletType>> m_bulletTypes;
};

// extrinsic (varying) part of the bullet
class Bullet {
  public:
    Bullet(int x, int y, const BulletType& bulletType) : m_x{x}, m_y{y}, m_bulletType{bulletType} {}
    void draw() const { m_bulletType.draw(m_x, m_y); }

  private:
    const BulletType& m_bulletType;
    const int m_x;
    const int m_y;
};

void client() {
    auto factory = std::make_unique<BulletFactory>();
    auto b1 = std::make_unique<Bullet>(5, 6, factory->getBulletType("Standard", 10));
    auto b2 = std::make_unique<Bullet>(11, 17, factory->getBulletType("Standard", 10));
    auto b3 = std::make_unique<Bullet>(22, 4, factory->getBulletType("Explosive", 20));
    b1->draw();
    b2->draw();
    b3->draw();
}

int main() { client(); }
