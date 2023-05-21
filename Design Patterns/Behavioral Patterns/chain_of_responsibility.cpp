// tasks: 1. add comments. 2. follow the best practices.

#include <iostream>
#include <memory>
#include <string>

class Logger {
  public:
    virtual ~Logger() = default;
    [[nodiscard]] virtual std::string handler(const std::string&) const = 0;
    virtual std::shared_ptr<Logger> setNext(const std::shared_ptr<Logger>&) = 0;
};

class AbstractLogger : public Logger {
  public:
    std::string handler(const std::string& request) const override {
        if (m_nextLogger) {
            return m_nextLogger->handler(request);
        }
        return {};
    }
    std::shared_ptr<Logger> setNext(const std::shared_ptr<Logger>& logger) override {
        m_nextLogger = logger;
        return m_nextLogger;
    }

  private:
    std::shared_ptr<Logger> m_nextLogger;
};

class ErrorLogger : public AbstractLogger {
  public:
    std::string handler(const std::string& request) const override {
        if (request == "error") {
            return "ErrorLogger handles the " + request + " request\n";
        }
        return AbstractLogger::handler(request);
    }
};

class WarningLogger : public AbstractLogger {
  public:
    std::string handler(const std::string& request) const override {
        if (request == "warning") {
            return "WarningLogger handles the " + request + " request\n";
        }
        return AbstractLogger::handler(request);
    }
};

class InfoLogger : public AbstractLogger {
  public:
    std::string handler(const std::string& request) const override {
        if (request == "info") {
            return "InfoLogger handles the " + request + " request\n";
        }
        return AbstractLogger::handler(request);
    }
};

void clientCode(const std::shared_ptr<Logger>& logger, const std::string& request) {
    std::cout << "Client sends a request: " << request << '\n';
    std::string result = logger->handler(request);
    if (!result.empty()) {
        std::cout << "Logger chain output: " << result << '\n';
    } else {
        std::cout << "The request was not handled by the logger chain." << '\n';
    }
}

int main() {
    auto errorLogger = std::make_shared<ErrorLogger>();
    auto warningLogger = std::make_shared<WarningLogger>();
    auto infoLogger = std::make_shared<InfoLogger>();
    errorLogger->setNext(warningLogger)->setNext(infoLogger);

    clientCode(errorLogger, "info");
    clientCode(errorLogger, "warning");
    clientCode(errorLogger, "error");
    clientCode(errorLogger, "debug");
}
