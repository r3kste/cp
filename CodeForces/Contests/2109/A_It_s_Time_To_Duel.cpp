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
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    bool possible = true;

    int s = 1;
    for (int i = 0; i < n - 1; i++) {
        s &= a[i];
        if (!(a[i] | a[i + 1])) {
            possible = false;
            break;
        }
    }
    s &= a[n - 1];

    if (s != 0) {
        possible = false;
    }

    if (possible) {
        cout << "NO";
    } else {
        cout << "YES";
    }

    cout << "\n";
}

int32_t main() {
    fastio;
    int t = 1;
    cin >> t;

    while (t--) {
        test();
    }

    return 0;
}