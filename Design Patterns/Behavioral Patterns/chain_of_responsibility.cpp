#include <iostream>
#include <memory>

// The Logger class defines the interface for handling requests.
class Logger {
  public:
    // Use pure virtual destructor to make the class abstract.
    virtual ~Logger() = 0;
    // Handles the given request. If this logger can't handle the request, it passes it to the next logger in
    // the chain.
    virtual void handler(const std::string_view request) const {
        if (m_nextLogger) {
            m_nextLogger->handler(request);
        } else {
            std::cout << request << " request wasn't handled.\n";
        }
    }

    // Sets the next logger in the chain and returns a reference to it.
    virtual Logger& setNext(std::shared_ptr<Logger> logger) {
        m_nextLogger = std::move(logger);
        return *m_nextLogger;
    }

  protected:
    // The next logger in the chain.
    std::shared_ptr<Logger> m_nextLogger;
};

// A pure virtual destructor still needs a definition, otherwise the program won't link.
Logger::~Logger() = default;

// The ErrorLogger class handles error requests.
class ErrorLogger : public Logger {
  public:
    // Handles error requests. If the request is not an error, it passes it to the next logger in the chain.
    void handler(const std::string_view request) const override {
        if (request == "error") {
            std::cout << "ErrorLogger handles the " << request << " request.\n";
        } else {
            Logger::handler(request);
        }
    }
};

// The WarningLogger class handles warning requests.
class WarningLogger : public Logger {
  public:
    // Handles warning requests. If the request is not a warning, it passes it to the next logger in the
    // chain.
    void handler(const std::string_view request) const override {
        if (request == "warning") {
            std::cout << "WarningLogger handles the " << request << " request.\n";
        } else {
            Logger::handler(request);
        }
    }
};

// The InfoLogger class handles info requests.
class InfoLogger : public Logger {
  public:
    // Handles info requests. If the request is not an info, it passes it to the next logger in the chain.
    void handler(const std::string_view request) const override {
        if (request == "info") {
            std::cout << "InfoLogger handles the " << request << " request.\n";
        } else {
            Logger::handler(request);
        }
    }
};

int main() {
    // Create loggers and set up the chain of responsibility.
    const auto error = std::make_shared<ErrorLogger>();
    const auto warning = std::make_shared<WarningLogger>();
    const auto info = std::make_shared<InfoLogger>();
    error->setNext(warning).setNext(info);

    // Send requests to a logger in the chain.
    warning->handler("error");
    warning->handler("warning");
    warning->handler("info");
    warning->handler("placeholder");
}
