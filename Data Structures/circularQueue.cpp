// this program implements a circular queue data structure and supports basic
// operations: enqueue, dequeue, isEmpty, isFull, peek.

#include <array>
#include <iostream>
#include <stdexcept>

template <typename T, int size> class Queue {
  private:
    std::array<T, size> m_queue{};
    int m_frontIndex{-1};
    int m_rearIndex{-1};

  public:
    bool isEmpty() { return (m_rearIndex == -1); }

    bool isFull() {
        if (m_rearIndex == m_frontIndex - 1) {
            return true;
        }
        if (m_frontIndex == 0 && m_rearIndex == size - 1) {
            return true;
        }
        return false;
    }

    void enqueue(const T& value) {
        if (!isFull()) {
            if (isEmpty()) {
                ++m_frontIndex;
            }
            m_rearIndex = (m_rearIndex + 1) % size;
            m_queue.at(m_rearIndex) = value;
        }
    }

    T dequeue() {
        if (!isEmpty()) {
            auto tempFrontIndex{m_frontIndex};
            if (m_frontIndex == m_rearIndex) {
                m_rearIndex = m_frontIndex = -1;
            }
            m_frontIndex = (m_frontIndex + 1) % size;
            return m_queue.at(tempFrontIndex);
        }
        throw std::out_of_range("dequeue out of range");
    }

    const T& peek() {
        if (!isEmpty()) {
            return m_queue.at(m_frontIndex);
        }
        throw std::out_of_range("peeking at an empty queue");
    }
};

int main() {
    using std::cout;
    cout << std::boolalpha;
    Queue<int, 3> intQueue{};
    cout << intQueue.isEmpty() << ' ' << intQueue.isFull() << '\n';
    intQueue.enqueue(5);
    cout << intQueue.isEmpty() << ' ' << intQueue.isFull() << '\n';
    intQueue.enqueue(7);
    intQueue.enqueue(9);
    cout << intQueue.isEmpty() << ' ' << intQueue.isFull() << '\n';
    cout << intQueue.peek() << '\n';
    cout << intQueue.dequeue() << '\n';
    intQueue.enqueue(11);
    cout << intQueue.dequeue() << '\n';
    intQueue.enqueue(13);
    cout << intQueue.dequeue() << '\n';
    intQueue.enqueue(15);
    cout << intQueue.peek() << '\n';
    cout << intQueue.isEmpty() << ' ' << intQueue.isFull() << '\n';
}
