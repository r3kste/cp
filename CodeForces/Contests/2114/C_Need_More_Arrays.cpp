#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

map<pair<int, int>, int> dp;
map<pair<int, int>, bool> dpd;

int f(int i, int last, vector<int> &a) {
    if (i == a.size()) {
        return 0;
    }

    if (dpd[{i, last}]) {
        return dp[{i, last}];
    }

    int ans = 0;
    if (a[i] > last + 1) {
        ans = 1;
        last = a[i];
    }

    // two choices: either delete a[i] or keep it
    // delete a[i]
    // keep a[i]
    ans += max(f(i + 1, last, a), f(i + 1, a[i], a));
    dpd[{i, last}] = true;
    dp[{i, last}] = ans;
    return ans;
}

void test() {
    int n;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int last = -1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > last + 1) {
            ans++;
            last = a[i];
        }
    }

    cout << ans << endl;

    // dpd.clear();
    // dp.clear();
    // int res = f(0, -1, a);
    // cout << res << endl;
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