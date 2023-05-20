#include <iostream>
#include <memory>

class OutputDevice {
  public:
    virtual ~OutputDevice() = default;
    virtual void output(const std::string_view) = 0;
};

class Speakers : public OutputDevice {
  public:
    void output(const std::string_view track) override {
        std::cout << "Playing \"" << track << "\" on speakers\n";
    }
};

class Headphones : public OutputDevice {
  public:
    void output(const std::string_view track) override {
        std::cout << "Playing \"" << track << "\" on headphones\n";
    }
};

class Player {
  public:
    Player(std::unique_ptr<OutputDevice> device) : m_device{std::move(device)} {}
    virtual ~Player() = default;
    virtual void play(const std::string_view track) { m_device->output(track); };

  protected:
    std::unique_ptr<OutputDevice> m_device;
};

class VLC : public Player {
  public:
    using Player::Player;
};

class Foobar2000 : public Player {
  public:
    using Player::Player;
};

int main() {
    auto outputDevice1 = std::make_unique<Speakers>();
    auto player1 = std::make_unique<VLC>(std::move(outputDevice1));
    player1->play("Periphery - The Bad Thing");

    auto outputDevice2 = std::make_unique<Headphones>();
    auto player2 = std::make_unique<Foobar2000>(std::move(outputDevice2));
    player2->play("Monuments - Doxa");
}
