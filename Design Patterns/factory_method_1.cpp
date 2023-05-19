#include <iostream>
#include <memory>
#include <string>

class Window {
  public:
    virtual ~Window() = default;
    virtual void Draw() const = 0;
};

class WindowsDialog : public Window {
  public:
    void Draw() const override { std::cout << "Drawing a Windows dialog..." << '\n'; }
};

class MacDialog : public Window {
  public:
    void Draw() const override { std::cout << "Drawing a Mac dialog..." << '\n'; }
};

class LinuxDialog : public Window {
  public:
    void Draw() const override { std::cout << "Drawing a Linux dialog..." << '\n'; }
};

enum class WindowType {
    Dialog,
};

enum class OSType {
    Windows,
    Mac,
    Linux,
};

// define an interface for concrete factory classes
class WindowFactory {
  public:
    virtual ~WindowFactory() = default;
    virtual std::unique_ptr<Window> CreateWindow(WindowType type) const = 0;
};

// concrete factory class that constructs a dialog window for windows
class WindowsWindowFactory : public WindowFactory {
  public:
    std::unique_ptr<Window> CreateWindow(WindowType type) const override {
        // choose the type of a window using enum constants
        if (type == WindowType::Dialog) {
            return std::make_unique<WindowsDialog>();
        }
        return nullptr;
    }
};

// concrete factory class that constructs a dialog window for mac
class MacWindowFactory : public WindowFactory {
  public:
    std::unique_ptr<Window> CreateWindow(WindowType type) const override {
        // choose the type of a window using enum constants
        if (type == WindowType::Dialog) {
            return std::make_unique<MacDialog>();
        }
        return nullptr;
    }
};

// concrete factory class that constructs a dialog window for linux
class LinuxWindowFactory : public WindowFactory {
  public:
    std::unique_ptr<Window> CreateWindow(WindowType type) const override {
        // choose the type of a window using enum constants
        if (type == WindowType::Dialog) {
            return std::make_unique<LinuxDialog>();
        }
        return nullptr;
    }
};

int main() {
    OSType os{OSType::Windows};
    std::unique_ptr<WindowFactory> factory;

    switch (os) {
        case OSType::Windows: factory = std::make_unique<WindowsWindowFactory>(); break;
        case OSType::Mac: factory = std::make_unique<MacWindowFactory>(); break;
        case OSType::Linux: factory = std::make_unique<LinuxWindowFactory>(); break;
        default: std::cerr << "Unsupported operating system\n";
    }

    auto dialog = factory->CreateWindow(WindowType::Dialog);
    dialog->Draw();
}
