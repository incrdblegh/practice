// this program implements a heap data structure with basic operations.

#include <algorithm>
#include <iostream>
#include <vector>

class Heap {
  private:
    std::vector<int> m_heap;

  public:
    void heapify();
    void insert(int value);
    void deleteNode(int value);
    void print();
};

void Heap::heapify() {
    int size{static_cast<int>(m_heap.size())};
    for (int internal{size / 2 - 1}; internal >= 0; --internal) {
        for (int child{1}; child <= 2; ++child) {
            int index{internal * 2 + child};
            if (index < size && m_heap.at(index) > m_heap.at(internal)) {
                std::swap(m_heap.at(index), m_heap.at(internal));
            }
        }
    }
}

void Heap::insert(int value) {
    m_heap.push_back(value);
    if (!m_heap.empty()) {
        heapify();
    }
}

void Heap::deleteNode(int value) {
    for (int& node : m_heap) {
        if (node == value) {
            std::swap(node, m_heap.at(m_heap.size() - 1));
            m_heap.pop_back();
            break;
        }
    }
    heapify();
}

void Heap::print() {
    for (const int& node : m_heap) {
        std::cout << node << ' ';
    }
    std::cout << '\n';
}

int main() {
    Heap intHeap;
    intHeap.insert(5);
    intHeap.print();
    intHeap.insert(6);
    intHeap.print();
    intHeap.insert(7);
    intHeap.print();
    intHeap.insert(8);
    intHeap.print();
    intHeap.deleteNode(8);
    intHeap.print();
}
