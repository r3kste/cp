#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
// #define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

void test() {
    int n, ret;
    cin >> n;
    if (n == 81) {
        cout << "mul 999999999" << endl;
        cin >> ret;
        cout << "digit" << endl;
        cin >> ret;
    } else {
        cout << "mul 999999999" << endl;
        cin >> ret;
        cout << "digit" << endl;
        cin >> ret;
        cout << "add " << n - 81 << endl;
        cin >> ret;
    }
    cout << "!" << endl;
    cin >> ret;
}

int32_t main() {
    // fastio;
    int t = 1;
    cin >> t;

    while (t--) {
        test();
    }

    return 0;
}