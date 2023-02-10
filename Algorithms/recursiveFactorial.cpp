// this program implements a recursive factorial algorithm. 

#include <iostream>

int calculateFactorial(int number) {
    if (number == 1) {
        return 1;
    }
    return number * calculateFactorial(number - 1);
}

int main() { std::cout << calculateFactorial(6) << '\n'; }
