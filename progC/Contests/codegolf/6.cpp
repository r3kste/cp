#include <iostream>
int main() {
    int t;
    std::cin >> t;

    while (t--) {
        std::cout << ((t % 2 == 0) ? "NO\n" : "YES\n");
    }
}