#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

void dfs(int i, vector<vector<int>> &adj, vector<bool> &visited) {
    visited[i] = true;
    for (int j : adj[i]) {
        if (!visited[j]) {
            dfs(j, adj, visited);
        }
    }
}

void test() {
    int n;
    cin >> n;
    vector<int> a;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (i > 0 && x == a.back()) {
            continue;
        }
        a.push_back(x);
    }

    int no_of_peaks = 0;
    for (int i = 1; i < a.size() - 1; i++) {
        if (a[i] > a[i - 1] && a[i] > a[i + 1]) {
            no_of_peaks++;
        }
    }

    if (a.size() == 1) {
        cout << 1 << endl;
        return;
    }

    if (a[1] < a[0]) {
        no_of_peaks++;
    }
    if (a[a.size() - 2] < a[a.size() - 1]) {
        no_of_peaks++;
    }

    cout << no_of_peaks << endl;
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