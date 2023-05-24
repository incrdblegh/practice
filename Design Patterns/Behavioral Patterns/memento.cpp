#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <string_view>

// The Memento class stores the internal state of a TextEditor object.
class Memento {
  public:
    // Constructor that takes the state of the TextEditor object as an argument.
    explicit Memento(const std::string_view state) : m_state{state} {}

  private:
    // The TextEditor class is a friend of the Memento class so it can access its private members.
    friend class TextEditor;
    // The internal state of the TextEditor object is stored as a const string.
    const std::string m_state;
};

// The TextEditor class represents a simple text editor that can insert and delete text.
class TextEditor {
  public:
    // Inserts the given text at the end of the current text.
    void insertText(const std::string_view text) { m_text += text; }
    // Deletes the last n characters from the current text.
    void deleteText(const int n) { m_text.erase(m_text.size() - n); }
    // Saves the current state of the TextEditor object by creating a new Memento object.
    std::unique_ptr<Memento> save() { return std::make_unique<Memento>(m_text); }
    // Restores the state of the TextEditor object from the given Memento object.
    void restore(const Memento& memento) { m_text = memento.m_state; }
    // Prints the current text to the standard output stream.
    void print() { std::cout << m_text << '\n'; }

  private:
    // The current text of the TextEditor object is stored as a string.
    std::string m_text;
};

// The Caretaker class manages a history of Mementos for a TextEditor object.
class Caretaker {
  public:
    // Constructor that takes a shared_ptr to a TextEditor object as an argument.
    Caretaker(std::shared_ptr<TextEditor> editor) : m_editor{std::move(editor)} {}
    // Saves the current state of the TextEditor object by calling its save method and storing
    // the resulting Memento object in a stack.
    void backup() { m_backups.push(m_editor->save()); }
    // Restores the TextEditor object to its previous state by popping the last Memento object
    // from the stack and calling the TextEditor's restore method with it.
    void undo() {
        if (m_backups.size() != 0) {
            m_editor->restore(*m_backups.top().get());
            m_backups.pop();
        }
    }

  private:
    // A shared_ptr to the TextEditor object whose state is being managed.
    const std::shared_ptr<TextEditor> m_editor;
    // A stack of unique_ptr to Memento objects representing the history of states for
    // the TextEditor object.
    std::stack<std::unique_ptr<Memento>> m_backups;
};

// A simple client function that demonstrates how to use the TextEditor, Memento, and Caretaker classes.
void client() {
    auto editor = std::make_shared<TextEditor>();
    auto caretaker = std::make_unique<Caretaker>(editor);
    editor->insertText("hello, ");
    editor->insertText("memento design pattern! yo duds");
    caretaker->backup();
    editor->print();
    editor->deleteText(7);
    editor->print();
    caretaker->undo();
    caretaker->undo();
    editor->print();
}

int main() { client(); }
