// this program implements a brace checker. 

#include <iostream>
#include <stack>

bool bracesCheck(const std::string& braces) {
    std::stack<char> checker;

    for (unsigned int i{0}; i < braces.length(); ++i) {
        if (checker.empty()) {
            checker.push(braces[i]);
        } else if ((checker.top() == '(' && braces[i] == ')') ||
                   (checker.top() == '{' && braces[i] == '}') ||
                   (checker.top() == '[' && braces[i] == ']')) {
            checker.pop();
        } else {
            checker.push(braces[i]);
        }
    }
    return checker.empty();
}

int main() {
    std::cout << bracesCheck("[{()}]") << '\n';
    std::cout << bracesCheck("[{[({(())}]") << '\n';
    std::cout << bracesCheck("[{((}[}[()]]))}]") << '\n';
    std::cout << bracesCheck("[{]}") << '\n';
}
