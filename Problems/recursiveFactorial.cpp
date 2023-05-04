// this program computes a factorial, potentially at compile-time

#include <iostream>

constexpr long long factorial(long long n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

int main() {
    std::cout << factorial(1) << '\n';
    std::cout << factorial(5) << '\n';
    std::cout << factorial(15) << '\n';
    std::cout << factorial(0) << '\n';
}
