// For the textbook definition of the Iterator design pattern this solution lacks abstract iterator and
// container base classes.
// This solution doesn't make use of the smart pointers, just like the iterators from the Standard Library.
// Copy operations make shallow copies.
// No support for move semantics.
// No support for cbegin() and cend().

#include <iostream>

// A templated linked list class that stores elements of type T.
template <typename T> class LinkedList {
    // Forward declaration of the Node struct.
    struct Node;

  public:
    // Appends a new element with the given value to the end of the linked list.
    LinkedList& append(T value) {
        if (m_head == nullptr) {
            // If the list is empty, create a new head node.
            m_head = new Node{value};
            m_tail = m_head;
        } else {
            // Otherwise, add a new node to the end of the list.
            m_tail->m_next = new Node{value};
            m_tail = m_tail->m_next;
        }
        return *this;
    }

    // An iterator class for iterating over the elements of the linked list.
    class Iterator {
      public:
        // Constructs an iterator that points to the given node.
        Iterator(Node* node) : m_current{node} {}

        // Returns true if this iterator is not equal to the given iterator.
        bool operator!=(const Iterator& iterator) { return m_current != iterator.m_current; }

        // Increments this iterator to point to the next element in the linked list.
        void operator++() { m_current = m_current->m_next; }

        // Returns a reference to the element pointed to by this iterator.
        T& operator*() { return m_current->m_data; }

      private:
        // A pointer to the current node in the linked list.
        Node* m_current{nullptr};
    };

    // Returns an iterator to the first element in the linked list.
    Iterator begin() { return Iterator{m_head}; }

    // Returns an iterator to one past the last element in the linked list.
    Iterator end() { return Iterator{nullptr}; }

  private:
    // A struct representing a node in the linked list.
    struct Node {
        T m_data{};            // The data stored in this node.
        Node* m_next{nullptr}; // A pointer to the next node in the linked list.
    };

    Node* m_head{nullptr}; // A pointer to the head of the linked list.
    Node* m_tail{nullptr}; // A pointer to the tail of the linked list.
};

int main() {
    LinkedList<int> newList;
    newList.append(5).append(6).append(7).append(8).append(9);

    for (const auto& element : newList) {
        std::cout << element << "->";
    }
    std::cout << '\n';
}
