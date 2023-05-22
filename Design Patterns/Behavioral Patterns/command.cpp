#include <iostream>
#include <memory>
#include <stack>

// The Calculator class provides basic arithmetic operations.
class Calculator {
  public:
    // Adds the given value to the current result.
    void add(int value) { m_result += value; }

    // Subtracts the given value from the current result.
    void sub(int value) { m_result -= value; }

    // Returns the current result of the calculation.
    [[nodiscard]] int getResult() const { return m_result; }

  private:
    // The current result of the calculation.
    int m_result{};
};

// The Command interface defines a common interface for all commands.
class Command {
  public:
    virtual ~Command() = default;

    // Constructs a new Command object with the given calculator and value.
    Command(const std::shared_ptr<Calculator> calculator, const int value)
        : m_calculator{std::move(calculator)}, m_value{value} {}

    // Executes the command.
    virtual void execute() const = 0;

    // Undoes the command.
    virtual void undo() const = 0;

  protected:
    // The calculator on which to perform the operation.
    const std::shared_ptr<Calculator> m_calculator;

    // The value to use in the operation.
    const int m_value{};
};

// The AddCommand class implements a command to add a value to the calculator's result.
class AddCommand : public Command {
  public:
    using Command::Command;

    // Executes the add command by adding the value to the calculator's result.
    void execute() const override { m_calculator->add(m_value); }

    // Undoes the add command by subtracting the value from the calculator's result.
    void undo() const override { m_calculator->sub(m_value); }
};

// The SubCommand class implements a command to subtract a value from the calculator's result.
class SubCommand : public Command {
  public:
    using Command::Command;

    // Executes the sub command by subtracting the value from the calculator's result.
    void execute() const override { m_calculator->sub(m_value); }

    // Undoes the sub command by adding the value to the calculator's result.
    void undo() const override { m_calculator->add(m_value); }
};

// The CommandInvoker class is responsible for invoking commands and maintaining a history of executed
// commands.
class CommandInvoker {
  public:
    // Sets the current command to be executed.
    void setCommand(std::unique_ptr<Command> command) { m_command = std::move(command); }

    // Executes the current command and adds it to the history of executed commands.
    void executeCommand() {
        m_command->execute();
        m_history.push(std::move(m_command));
    }

    // Undoes the most recently executed command and removes it from the history of executed commands.
    void undoCommand() {
        if (m_history.empty()) {
            return;
        }
        auto command = std::move(m_history.top());
        command->undo();
        m_history.pop();
    }

  private:
    // The current command to be executed.
    std::unique_ptr<Command> m_command;

    // A stack of executed commands that can be undone.
    std::stack<std::unique_ptr<Command>> m_history;
};

int main() {
    auto calculator = std::make_shared<Calculator>();
    auto invoker = std::make_unique<CommandInvoker>();

    invoker->setCommand(std::make_unique<AddCommand>(calculator, 5));
    invoker->executeCommand();

    invoker->setCommand(std::make_unique<AddCommand>(calculator, 8));
    invoker->executeCommand();

    std::cout << "Result after two additions: " << calculator->getResult() << '\n';

    invoker->undoCommand();
    std::cout << "Result after one undo: " << calculator->getResult() << '\n';

    invoker->undoCommand();
    std::cout << "Result after one undo: " << calculator->getResult() << '\n';
}
