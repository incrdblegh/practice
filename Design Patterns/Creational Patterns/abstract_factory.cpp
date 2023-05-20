// the following code implements the Abstract Factory design pattern. it has barely any comments, mostly
// because at the time of writing it looked self-explanatory. we'll see how this assumption will age

#include <iostream>
#include <memory>

class Window {
  public:
    virtual ~Window() = default;
    virtual void draw() = 0;
};

class WindowsWindow : public Window {
  public:
    ~WindowsWindow() override = default;
    void draw() override { std::cout << "Drawing a Windows window\n"; };
};

class MacWindow : public Window {
  public:
    ~MacWindow() override = default;
    void draw() override { std::cout << "Drawing a Mac window\n"; };
};

class LinuxWindow : public Window {
  public:
    ~LinuxWindow() override = default;
    void draw() override { std::cout << "Drawing a Linux window\n"; };
};

class Factory {
  public:
    virtual ~Factory() = default;
    // overrides in the derived classes won't be able to ignore the return value of createWindow
    [[nodiscard]] virtual std::unique_ptr<Window> createWindow() = 0;
};

class WindowsFactory : public Factory {
  public:
    ~WindowsFactory() override = default;
    std::unique_ptr<Window> createWindow() override { return std::make_unique<WindowsWindow>(); }
};

class MacFactory : public Factory {
  public:
    ~MacFactory() override = default;
    std::unique_ptr<Window> createWindow() override { return std::make_unique<MacWindow>(); };
};

class LinuxFactory : public Factory {
  public:
    ~LinuxFactory() override = default;
    std::unique_ptr<Window> createWindow() override { return std::make_unique<LinuxWindow>(); };
};

enum class OS {
    Windows,
    Mac,
    Linux,
};

std::unique_ptr<Factory> getFactory(const OS os) {
    switch (os) {
        case OS::Windows: return std::make_unique<WindowsFactory>();
        case OS::Mac: return std::make_unique<MacFactory>();
        case OS::Linux: return std::make_unique<LinuxFactory>();
        default: std::cerr << "No compatible OS\n"; return nullptr;
    }
}

int main() {
    constexpr OS os = OS::Linux;
    // use if with initializer to check whether getFactory succeeded
    if (auto factory = getFactory(os); factory) {
        auto window = factory->createWindow();
        window->draw();
    }
}
