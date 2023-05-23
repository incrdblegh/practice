#include <iostream>
#include <stack>

bool bracesCheck(const std::string& braces) {
    // Create a stack to keep track of opening brackets
    std::stack<char> matcher;

    // Iterate over each character in the input string
    for (const auto& brace : braces) {
        // If the character is an opening bracket, push it onto the stack
        if (brace == '(' || brace == '{' || brace == '[') {
            matcher.push(brace);
        } else {
            // If the stack is empty or the top of the stack doesn't match the closing bracket, return false
            if (matcher.empty() || (matcher.top() == '(' && brace != ')') ||
                (matcher.top() == '{' && brace != '}') || (matcher.top() == '[' && brace != ']')) {
                return false;
            }
            // Pop the top of the stack
            matcher.pop();
        }
    }
    // If the stack is empty at the end, all pairs of parentheses match and are nested correctly
    return matcher.empty();
}

int main() {
    std::cout << std::boolalpha;
    std::cout << bracesCheck("()") << std::endl;      // prints true
    std::cout << bracesCheck("[]") << std::endl;      // prints true
    std::cout << bracesCheck("{}") << std::endl;      // prints true
    std::cout << bracesCheck("({[]})") << std::endl;  // prints true
    std::cout << bracesCheck("(") << std::endl;       // prints false
    std::cout << bracesCheck(")") << std::endl;       // prints false
    std::cout << bracesCheck("(}") << std::endl;      // prints false
    std::cout << bracesCheck("([)]") << std::endl;    // prints false
    std::cout << bracesCheck("") << std::endl;        // prints true
    std::cout << bracesCheck("()[]{}") << std::endl;  // prints true
    std::cout << bracesCheck("a") << std::endl;       // prints false
    std::cout << bracesCheck("()[b]{}") << std::endl; // prints false
}
