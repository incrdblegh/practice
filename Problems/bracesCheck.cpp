#include <iostream>
#include <stack>

bool bracesCheck(const std::string& braces) {
    // if the number of braces is odd, then the sequence is invalid
    if (braces.length() % 2 == 1) {
        return false;
    }
    std::stack<char> checker;

    for (const auto& brace : braces) {
        // add a valid opening brace to the checker
        if (brace == '(' || brace == '{' || brace == '[') {
            checker.push(brace);
        } else {
            // if current brace is not the opening one, and the checker is empty, then the brace is
            // an invalid character
            if (checker.empty()) {
                return false;
            }
            // store the value to avoid multiple evaluations in if statement
            char top = checker.top();
            // pop the matching brace
            checker.pop();
            // the sequence is invalid if current brace and previous checker brace don't match
            if ((brace == ')' && top != '(') || (brace == '}' && top != '{') ||
                (brace == ']' && top != '[')) {
                return false;
            }
        }
    }
    // return true if the sequence is empty, either because all matching braces were popped, or the
    // string passed to the function was empty
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
