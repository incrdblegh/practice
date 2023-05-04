// the following solution performs on average 2-2.5 times worse compared to the usual solution with
// the || brace checks in if statements, but in turns it's easier to read and extend

#include <iostream>
#include <stack>
#include <unordered_map>

bool bracesCheck(const std::string& braces) {
    std::stack<char> checker;
    std::unordered_map<char, char> matchingBraces = {{')', '('}, {'}', '{'}, {']', '['}};

    for (const auto& brace : braces) {
        if (matchingBraces.count(brace) == 0) {
            checker.push(brace);
        } else {
            if (checker.empty() || checker.top() != matchingBraces[brace]) {
                return false;
            }
            checker.pop();
        }
    }
    return checker.empty();
}

int main() {
    std::cout << std::boolalpha << bracesCheck("()") << std::endl;      // prints true
    std::cout << std::boolalpha << bracesCheck("[]") << std::endl;      // prints true
    std::cout << std::boolalpha << bracesCheck("{}") << std::endl;      // prints true
    std::cout << std::boolalpha << bracesCheck("({[]})") << std::endl;  // prints true
    std::cout << std::boolalpha << bracesCheck("(") << std::endl;       // prints false
    std::cout << std::boolalpha << bracesCheck(")") << std::endl;       // prints false
    std::cout << std::boolalpha << bracesCheck("(}") << std::endl;      // prints false
    std::cout << std::boolalpha << bracesCheck("([)]") << std::endl;    // prints false
    std::cout << std::boolalpha << bracesCheck("") << std::endl;        // prints true
    std::cout << std::boolalpha << bracesCheck("()[]{}") << std::endl;  // prints true
    std::cout << std::boolalpha << bracesCheck("a") << std::endl;       // prints false
    std::cout << std::boolalpha << bracesCheck("()[b]{}") << std::endl; // prints false
}
