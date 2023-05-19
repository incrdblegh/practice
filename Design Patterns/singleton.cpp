class Singleton final {
  public:
    static Singleton& getInstance() {
        static Singleton* instance = new Singleton;
        return *instance;
    }
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

  private:
    Singleton() = default;
};
