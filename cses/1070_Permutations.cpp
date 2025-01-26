#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

void test() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    if (n < 4) {
        cout << "NO SOLUTION" << endl;
        return;
    }

    if (n % 2 == 0) {
        for (int i = n - 1; i >= 1; i -= 2) {
            cout << i << " ";
        }

        for (int i = n; i >= 2; i -= 2) {
            cout << i << " ";
        }
    } else  {
        for (int i = n; i >= 1; i -= 2) {
            cout << i << " ";
        }

        for (int i = n - 1; i >= 2  ; i -= 2) {
            cout << i << " ";
        }
    }
}

int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;

    while (t--) {
        test();
    }

    return 0;
}