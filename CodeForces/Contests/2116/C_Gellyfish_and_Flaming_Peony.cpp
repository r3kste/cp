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

    if (n == 1) {
        cout << 0 << endl;
        return;
    }

    int total_gcd = a[0];
    for (int i = 1; i < n; i++) {
        total_gcd = __gcd(total_gcd, a[i]);
    }

    int cnt_gcd = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == total_gcd) {
            cnt_gcd++;
        }
    }
    if (cnt_gcd > 0) {
        cout << n - cnt_gcd << endl;
    } else {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());

        int maxim = a.back();
        // dist[e] is minimum number of operations to somehow reach e
        vector<int> dist(maxim + 1, -1);

        queue<int> q;
        for (int e : a) {
            dist[e] = 0;
            q.push(e);
        }

        while (!q.empty()) {
            int e = q.front();
            q.pop();

            if (e == total_gcd) {
                break;
            }

            for (int other : a) {
                int d = __gcd(e, other);
                if (dist[d] == -1) {
                    // if not visited
                    dist[d] = dist[e] + 1;
                    q.push(d);
                }
            }
        }

        // somehow reach total_gcd
        int ops = dist[total_gcd];
        ops += (n - 1);
        cout << ops << endl;
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