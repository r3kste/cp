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
        int x;
        cin >> x;
        a[i] = abs(x);
    }

    int first = a[0];

    sort(a.begin(), a.end());
    int req = (n - 1) / 2;

    int lb = lower_bound(a.begin(), a.end(), first) - a.begin();

    if (lb < n - req) {
        cout << "YES" << endl;
        return;
    }
    cout << "NO" << endl;
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