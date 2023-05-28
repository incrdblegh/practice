#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

// An abstrat class with a template method 'Sort'.
class Sorter {
  public:
    virtual ~Sorter() = default;
    virtual void sort(std::vector<int>& data) {
        for (int i = 0; i < data.size() - 1; ++i) {
            for (int j = 0; j < data.size() - 1 - i; ++j) {
                if (compare(data[j], data[j + 1])) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

  protected:
    // Steps of the template method.
    virtual bool compare(const int a, const int b) const = 0;
    virtual void swap(int& first, int& second) { std::swap(first, second); }
};

// Concrete implementation of a step of the template method.
class AscendingSorter : public Sorter {
  protected:
    bool compare(const int a, const int b) const override { return a < b; }
};

// Concrete implementation of a step of the template method.
class DescendingSorter : public Sorter {
  protected:
    bool compare(const int a, const int b) const override { return a > b; }
};

void print(const std::vector<int>& data) {
    for (const auto& piece : data) {
        std::cout << piece << ' ';
    }
    std::cout << '\n';
}

void client() {
    std::vector data{3, 6, 8, 3, 1, 4, 2};
    print(data);
    auto ascSorter = std::make_unique<AscendingSorter>();
    ascSorter->sort(data);
    print(data);
    auto descSorter = std::make_unique<DescendingSorter>();
    descSorter->sort(data);
    print(data);
}

int main() { client(); }
