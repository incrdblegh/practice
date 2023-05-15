class Singleton {
  private:
    Singleton() = default;

  public:
    static Singleton& getInstance() {
        // this doesn't cause memory leaks, 'new' will be called only once.
        // this approach is also thread-safe, and doesn't require explicit synchronization
        static Singleton* instance = new Singleton;
        return *instance;
        // no need for explicit deallocation, the resource is freed when the program finishes running
    }

    // explicitly deleting copy and move operations 
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

// static memory allocation might be preferred if the resource held by the singleton is trivial
// static Singleton& get_instance() {
//     static Singleton instance;
//     return instance;
// }
