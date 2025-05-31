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
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    if (min(a, c) < min(b, d)) {
        cout << "Flower" << endl;
    } else if (min(a, c) >= min(b, d)) {
        cout << "Gellyfish" << endl;
    } else {
    }
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