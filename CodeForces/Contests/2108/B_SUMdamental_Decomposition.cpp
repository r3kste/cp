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
    int n, x;
    cin >> n >> x;

    auto bitset_x = bitset<32>(x);
    auto bitset_a = bitset<32>(0);
    auto bitset_b = bitset<32>(0);

    if (x == 1) {
        if (n % 2) {
            cout << n << endl;
        } else {
            cout << n + 3 << endl;
        }
        return;
    }
    if (x == 0) {
        if (n % 2 == 0) {
            cout << n << endl;
        } else {
            if (n == 1) {
                cout << -1 << endl;
            } else {
                cout << n + 3 << endl;
            }
        }
        return;
    }
    int sum = 0;
    int high_bits = bitset_x.count();
    n -= high_bits;

    sum = x;

    if (n <= 0) {
        cout << sum << endl;
        return;
    }

    sum += n;

    int total_ones = n + (x % 2 == 1);
    if (bitset_x[0] == 1) {
        if (total_ones % 2 == 0) {
            sum += 1;
        }
    } else {
        if (total_ones % 2 == 1) {
            sum += 1;
        }
    }
    cout << sum << endl;
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