#include "bits/stdc++.h"
using namespace std;

typedef long long int ll;
#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(998244353)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

ll power(ll x, ll y, ll mod) {
    ll res = 1;
    x %= mod;

    while (y > 0) {
        if (y & 1) {
            res = (res * x) % mod;
        }

        y >>= 1;
        x = (x * x) % mod;
    }

    return res;
}

void test() {
    int n;
    cin >> n;
    vector<int> p(n);

    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    vector<int> q(n);

    for (int i = 0; i < n; i++) {
        cin >> q[i];
    }

    vector<int> maxp(n);
    vector<int> maxq(n);

    maxp[0] = 0;
    int maxim = p[0];
    int maxidx = 0;
    for (int i = 1; i < n; i++) {
        if (p[i] > maxim) {
            maxim = p[i];
            maxidx = i;
        }
        maxp[i] = maxidx;
    }

    maxq[0] = 0;
    maxim = q[0];
    maxidx = 0;
    for (int i = 1; i < n; i++) {
        if (q[i] > maxim) {
            maxim = q[i];
            maxidx = i;
        }
        maxq[i] = maxidx;
    }

    vector<int> r(n);

    for (int i = 0; i < n; i++) {
        int p_idx = maxp[i];
        int q_idx = maxq[i];

        int larger = max(p[p_idx], q[q_idx]);
        int smaller;
        if (p[p_idx] > q[q_idx]) {
            smaller = q[i - p_idx];
        } else if (p[p_idx] < q[q_idx]) {
            smaller = p[i - q_idx];
        } else {
            smaller = max(q[i - p_idx], p[i - q_idx]);
        }
        r[i] = power(2, larger, MOD);
        r[i] += power(2, smaller, MOD);
        r[i] %= MOD;
    }

    for (int i = 0; i < n; i++) {
        cout << r[i] << " ";
    }
    cout << endl;
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