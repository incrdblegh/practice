#include <iostream>
#include <memory>

// Abstract base class representing an output device for playing audio.
class OutputDevice {
  public:
    virtual ~OutputDevice() = default;

    // Plays the given audio track on the output device.
    virtual void output(const std::string_view) const = 0;
};

// Concrete class representing speakers as an output device.
class Speakers : public OutputDevice {
  public:
    // Plays the given audio track on the speakers.
    void output(const std::string_view track) const override {
        std::cout << "Playing \"" << track << "\" on speakers\n";
    }
};

// Concrete class representing headphones as an output device.
class Headphones : public OutputDevice {
  public:
    // Plays the given audio track on the headphones.
    void output(const std::string_view track) const override {
        std::cout << "Playing \"" << track << "\" on headphones\n";
    }
};

// Abstract base class representing a media player.
class Player {
  public:
    // Constructs a media player with the given output device.
    Player(std::unique_ptr<OutputDevice> device) : m_device{std::move(device)} {}

    virtual ~Player() = 0;

    // Plays the given audio track using the media player's output device.
    virtual void play(const std::string_view track) const { m_device->output(track); };

  protected:
    // The output device used by the media player to play audio.
    std::unique_ptr<OutputDevice> m_device;
};

Player::~Player() = default;

// Concrete class representing the VLC media player.
class VLC : public Player {
  public:
    using Player::Player;

    // Starts the VLC media player and plays the given audio track.
    void play(const std::string_view track) const override {
        std::cout << "Starting VLC...\n";
        Player::play(track);
    }
};

// Concrete class representing the Foobar2000 media player.
class Foobar2000 : public Player {
  public:
    using Player::Player;

    // Starts the Foobar2000 media player and plays the given audio track.
    void play(const std::string_view track) const override {
        std::cout << "Starting Foobar2000...\n";
        Player::play(track);
    }
};

int main() {
    // Create a VLC media player with speakers as the output device and play a track.
    auto outputDevice1 = std::make_unique<Speakers>();
    auto player1 = std::make_unique<VLC>(std::move(outputDevice1));
    player1->play("Periphery - The Bad Thing");

    // Create a Foobar2000 media player with headphones as the output device and play a track.
    auto outputDevice2 = std::make_unique<Headphones>();
    auto player2 = std::make_unique<Foobar2000>(std::move(outputDevice2));
    player2->play("Monuments - Doxa");
}
