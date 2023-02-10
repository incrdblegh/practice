// this program implements a deque data structure with the following operations:
// isFull, isEmpty, getFront, getRear, reset, pushFront, popFront, pushRear,
// popRear, print.

#include <array>
#include <iostream>
#include <stdexcept>

template <typename T, int size> class Deque {
  private:
    std::array<T, size> m_deque{};
    int m_front{-1};
    int m_rear{0};

  public:
    bool isFull() { return (m_rear + 1) % size == m_front; }
    bool isEmpty() { return m_front == -1; }
    T getFront() { return m_deque.at(m_front); }
    T getRear() { return m_deque.at(m_rear); }

    void reset() {
        m_front = -1;
        m_rear = 0;
    }

    void pushFront(T value) {
        if (!isFull()) {
            if (isEmpty()) {
                ++m_front;
            } else if (m_front == 0) {
                m_front = size - 1;
            } else {
                --m_front;
            }
            m_deque.at(m_front) = value;
        }
    }

    void popFront() {
        if (!isEmpty()) {
            if (m_front == m_rear) {
                reset();
            } else if ((m_front + 1) % size == 0) {
                m_front = 0;
            } else {
                ++m_front;
            }
        }
    }

    void pushRear(T value) {
        if (!isFull()) {
            if (isEmpty()) {
                ++m_front;
            } else if ((m_rear + 1) % size == 0) {
                m_rear = 0;
            } else {
                ++m_rear;
            }
            m_deque.at(m_rear) = value;
        }
    }

    void popRear() {
        if (!isEmpty()) {
            if (m_rear == m_front) {
                reset();
            } else if (m_rear == 0) {
                m_rear = size - 1;
            } else {
                --m_rear;
            }
        }
    }

    void print() {
        for (T& element : m_deque) {
            std::cout << element << ' ';
        }
        std::cout << '\n';
    }
};

int main() {
    using std::cout;
    Deque<int, 3> intDeque{};
    std::cout << intDeque.isEmpty() << ' ' << intDeque.isFull() << '\n';
    intDeque.pushRear(7);
    intDeque.pushRear(8);
    std::cout << intDeque.isEmpty() << ' ' << intDeque.isFull() << '\n';
    intDeque.pushFront(6);
    std::cout << intDeque.isEmpty() << ' ' << intDeque.isFull() << '\n';
    intDeque.print();
    intDeque.popRear();
    intDeque.popFront();
    intDeque.popFront();
    std::cout << intDeque.isEmpty() << ' ' << intDeque.isFull() << '\n';
}
