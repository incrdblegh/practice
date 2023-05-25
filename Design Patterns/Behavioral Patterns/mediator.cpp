#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

// Forward declaration of the User class.
class User;

// The Mediator abstract base class defines a common interface for all mediators.
class Mediator {
  public:
    // Virtual destructor to allow for proper destruction of derived objects through a base class pointer.
    virtual ~Mediator() = default;

    // Pure virtual method to add a user to the mediator.
    virtual void addUser(const std::shared_ptr<User> user) = 0;

    // Pure virtual method to send a message from one user to all other users through the mediator.
    virtual void sendMessage(const std::string_view message, int userID) const = 0;
};

// The User class represents a colleague object that communicates with other colleagues through the mediator.
class User {
  public:
    // Constructor that takes the user's ID, name, and a shared pointer to the mediator object.
    User(const int id, const std::string_view name, std::shared_ptr<Mediator> mediator)
        : m_id{id}, m_name{name}, m_mediator{std::move(mediator)} {}

    // Method to send a message through the mediator.
    void send(const std::string_view message) const { m_mediator->sendMessage(message, m_id); }

    // Method to receive a message from another user through the mediator.
    void receive(const std::string_view message) const {
        std::cout << "User " << m_name << " received a message: " << message << '\n';
    }

    // Getter method for the user's ID.
    int getID() const { return m_id; }

  private:
    // The user's ID.
    const int m_id{};

    // The user's name.
    const std::string m_name;

    // A shared pointer to the mediator object.
    const std::shared_ptr<Mediator> m_mediator;
};

// The ChatRoom class is a concrete mediator that implements the Mediator interface.
class ChatRoom : public Mediator {
  public:
    // Method to add a user to the chat room.
    void addUser(const std::shared_ptr<User> user) override { m_users[user->getID()] = std::move(user); }

    // Method to send a message from one user to all other users in the chat room through the mediator.
    void sendMessage(const std::string_view message, int userID) const override {
        if (m_users.count(userID)) {
            std::cout << "User ID::" << userID << " sent a message.\n";
            for (const auto& [id, user] : m_users) {
                if (id != userID) {
                    user->receive(message);
                }
            }
        }
    }

  private:
    // An unordered map that associates user IDs with shared pointers to User objects.
    std::unordered_map<int, std::shared_ptr<User>> m_users;
};

int main() {
    // Create a shared pointer to a ChatRoom object.
    const auto chat = std::make_shared<ChatRoom>();

    // Create shared pointers to several User objects and add them to the chat room.
    const auto Mark = std::make_shared<User>(1, "Mark", chat);
    const auto John = std::make_shared<User>(2, "John", chat);
    const auto Sam = std::make_shared<User>(3, "Sam", chat);
    const auto Dean = std::make_shared<User>(4, "Dean", chat);
    const auto Derek = std::make_shared<User>(5, "Derek", chat);
    chat->addUser(Mark);
    chat->addUser(John);
    chat->addUser(Sam);
    chat->addUser(Dean);
    chat->addUser(Derek);
    Sam->send("yo bros");
}
