// this program implements a brace checker.

#include <iostream>
#include <stack>

bool bracesCheck(const std::string& braces) {
    if (braces.empty()) {
        return false;
    }
    std::stack<char> checker;

    for (const auto& brace : braces) {
        if (checker.empty()) {
            checker.push(brace);
        } else if ((checker.top() == '(' && brace == ')') ||
                   (checker.top() == '{' && brace == '}') ||
                   (checker.top() == '[' && brace == ']')) {
            checker.pop();
        } else {
            checker.push(brace);
        }
    }
    return checker.empty();
}

int main() {
    std::cout << bracesCheck("[{()}]") << '\n'; // the only true case
    std::cout << bracesCheck("") << '\n';       // the rest are false
    std::cout << bracesCheck(" ") << '\n';
    std::cout << bracesCheck("     ") << '\n';
    std::cout << bracesCheck("[{[({(())}]") << '\n';
    std::cout << bracesCheck("[{((}[}[()]]))}]") << '\n';
    std::cout << bracesCheck("[{]}") << '\n';
    std::cout << bracesCheck("gfdoqGSHOG \n5435`~':^#$)") << '\n';
}
