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

    vector<vector<int>> grid(n, vector<int>(n));

    int top = 0, left = 0, bottom = n - 1, right = n - 1;
    int num = n * n - 1;

    while (top <= bottom && left <= right) {
        // Fill the top row
        for (int i = left; i <= right; ++i) {
            grid[top][i] = num--;
        }
        top++;

        // Fill the right column
        for (int i = top; i <= bottom; ++i) {
            grid[i][right] = num--;
        }
        right--;

        // Fill the bottom row
        if (top <= bottom) {
            for (int i = right; i >= left; --i) {
                grid[bottom][i] = num--;
            }
            bottom--;
        }

        // Fill the left column
        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                grid[i][left] = num--;
            }
            left++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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