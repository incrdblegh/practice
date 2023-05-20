#include <iostream>

template <typename Derived> class Singleton {
  public:
    static Derived& getInstance() {
        static Derived* instance = new Derived;
        return *instance;
    }
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

  protected:
    Singleton() = default;
};

class DerivedSingleton : public Singleton<DerivedSingleton> {
  public:
    void print() const { std::cout << "Hello from a derived singleton!\n"; }

  private:
    friend Singleton;
    DerivedSingleton() = default;
};

int main() {
    DerivedSingleton& derived = DerivedSingleton::getInstance();
    derived.print();
}
