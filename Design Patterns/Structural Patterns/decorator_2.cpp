#include <iostream>
#include <memory>
#include <string>

// The TextFormatter class defines a common interface for formatting text.
class TextFormatter {
  public:
    // Virtual destructor to allow for proper cleanup of derived classes.
    virtual ~TextFormatter() = default;

    // Pure virtual function to format a given string.
    [[nodiscard]] virtual std::string format(const std::string&) const = 0;
};

// The PlainTextFormatter class formats text as plain text.
class PlainTextFormatter : public TextFormatter {
  public:
    // Formats the given string as plain text.
    std::string format(const std::string& str) const override { return str; }
};

// The AbstractTextFormatter class provides a base class for text formatters that decorate other text
// formatters.
class AbstractTextFormatter : public TextFormatter {
  public:
    // Constructs an AbstractTextFormatter object with the given formatter.
    AbstractTextFormatter(std::unique_ptr<TextFormatter> formatter) : m_formatter{std::move(formatter)} {}

    // Formats the given string using the decorated formatter.
    std::string format(const std::string& str) const override { return m_formatter->format(str); }

  private:
    // The decorated formatter.
    std::unique_ptr<TextFormatter> m_formatter;
};

// The BoldTextFormatter class formats text as bold text.
class BoldTextFormatter : public AbstractTextFormatter {
  public:
    // Inherit the constructors of the base class.
    using AbstractTextFormatter::AbstractTextFormatter;

    // Formats the given string as bold text.
    std::string format(const std::string& str) const override {
        return "<b>" + AbstractTextFormatter::format(str) + "</b>";
    }
};

// The ItalicTextFormatter class formats text as italic text.
class ItalicTextFormatter : public AbstractTextFormatter {
  public:
    // Inherit the constructors of the base class.
    using AbstractTextFormatter::AbstractTextFormatter;

    // Formats the given string as italic text.
    std::string format(const std::string& str) const override {
        return "<i>" + AbstractTextFormatter::format(str) + "</i>";
    }
};

// The UnderlineTextFormatter class formats text as underlined text.
class UnderlineTextFormatter : public AbstractTextFormatter {
  public:
    // Inherit the constructors of the base class.
    using AbstractTextFormatter::AbstractTextFormatter;

    // Formats the given string as underlined text.
    std::string format(const std::string& str) const override {
        return "<u>" + AbstractTextFormatter::format(str) + "</u>";
    }
};

int main() {
    // Create a formatter that formats text as underlined, italic, and bold text.
    auto formatter = std::make_unique<UnderlineTextFormatter>(std::make_unique<ItalicTextFormatter>(
        std::make_unique<BoldTextFormatter>(std::make_unique<PlainTextFormatter>())));

    // Format a string using the created formatter and print it to the standard output stream.
    std::cout << formatter->format("hello, the world of design patterns!");
}
