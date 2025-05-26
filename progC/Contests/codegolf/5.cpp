#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, a = 0, b = 0;
    cin >> n;
    int ans;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;

            if (i == j) {
                continue;
            }

            if (!a) {
                a = x;
            } else if (!b) {
                b = x;
                ans = __gcd(a, b);
            } else {
                ans = __gcd(ans, x);
            }
        }

        cout << ans << ' ';
        a = 0;
        b = 0;
    }
}