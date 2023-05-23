#include <iostream>

// Template class for implementing the Singleton pattern
template <typename Derived> class Singleton {
  public:
    // Static method to get a reference to the singleton instance
    static Derived& getInstance() {
        // Create a static instance of the Derived type
        static Derived instance;
        // Return a reference to the instance
        return instance;
    }

    // Delete copy and move constructors and assignment operators to prevent multiple instances
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

  protected:
    // Default constructor is protected to prevent direct instantiation
    Singleton() = default;
};

// Derived class that inherits from the Singleton template class
class DerivedSingleton : public Singleton<DerivedSingleton> {
  public:
    // Public method to demonstrate functionality
    void print() const { std::cout << "Hello from a derived singleton!\n"; }

  private:
    // Declare the base class as a friend to allow it to access the private constructor
    friend Singleton<DerivedSingleton>;
    // Private constructor to prevent direct instantiation
    DerivedSingleton() = default;
};

int main() {
    // Get a reference to the singleton instance of the DerivedSingleton class
    DerivedSingleton& derived = DerivedSingleton::getInstance();
    // Call the print method on the singleton instance
    derived.print();
}
