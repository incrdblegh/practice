#include <iostream>

int countDigits(int n) {
    if (n == 0) {
        return 1;
    }
    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    return count;
}

int main() {
    std::cout << countDigits(12345) << '\n';  // 5
    std::cout << countDigits(0) << '\n';      // 1
    std::cout << countDigits(9) << '\n';      // 1
    std::cout << countDigits(100000) << '\n'; // 6
}
