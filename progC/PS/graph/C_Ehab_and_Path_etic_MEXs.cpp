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
    vector<vector<int>> adj(n + 1);
    vector<int> mex_vals(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(i);
        adj[v].push_back(i);
        mex_vals[i] = -1;
    }
    pair<int, int> max_neighbor(0, 0);

    for (int i = 1; i <= n; i++) {
        max_neighbor = max(max_neighbor, make_pair((int)adj[i].size(), i));
    }
    int cur = 0;

    for (int i : adj[max_neighbor.second]) {
        mex_vals[i] = cur++;
    }
    for (int i = 1; i < n; i++) {
        if (mex_vals[i] == -1) {
            mex_vals[i] = cur++;
        }

        cout << mex_vals[i] << endl;
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