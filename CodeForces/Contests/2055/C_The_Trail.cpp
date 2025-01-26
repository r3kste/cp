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
    int n, m;
    cin >> n >> m;
    string path;
    cin >> path;
    int grid[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    vector<int> row_sums(n, 0);
    vector<int> col_sums(m, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            row_sums[i] += grid[i][j];
            col_sums[j] += grid[i][j];
        }
    }

    pair<int, int> pos = make_pair(0, 0);

    for (char c : path) {
        if (c == 'D') {
            int a = -row_sums[pos.first];
            grid[pos.first][pos.second] = a;
            row_sums[pos.first] = 0;
            col_sums[pos.second] += a;
            pos.first++;
        } else {
            int a = -col_sums[pos.second];
            grid[pos.first][pos.second] = a;
            col_sums[pos.second] = 0;
            row_sums[pos.first] += a;
            pos.second++;
        }
    }

    grid[pos.first][pos.second] = -row_sums[pos.first];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << grid[i][j] << " ";
        }

        cout << endl;
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
