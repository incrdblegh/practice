#include <iostream>
#include <type_traits>

// Recursive case.
template <int N> struct Fibonacci {
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

// Base case for n == 0.
template <> struct Fibonacci<0> {
    static constexpr int value = 0;
};

// Base case for n == 1.
template <> struct Fibonacci<1> {
    static constexpr int value = 1;
};

// An alternative solution with constexpr; can be replaced with consteval in C++20.
// constexpr int Fibonacci(int N) {
//     if (N == 0)
//         return 0;
//     if (N == 1)
//         return 1;
//     return Fibonacci(N - 1) + Fibonacci(N - 2);
// }

int main() {
    // Test case 1: Fibonacci<0>
    static_assert(Fibonacci<0>::value == 0);

    // Test case 2: Fibonacci<1>
    static_assert(Fibonacci<1>::value == 1);

    // Test case 3: Fibonacci<2>
    static_assert(Fibonacci<2>::value == 1);

    // Test case 4: Fibonacci<3>
    static_assert(Fibonacci<3>::value == 2);

    // Test case 5: Fibonacci<4>
    static_assert(Fibonacci<4>::value == 3);

    // Test case 6: Fibonacci<5>
    static_assert(Fibonacci<5>::value == 5);

    // Test case 7: Fibonacci<10>
    static_assert(Fibonacci<10>::value == 55);
}
