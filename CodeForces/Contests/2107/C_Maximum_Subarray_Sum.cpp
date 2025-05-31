#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e13)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

void test() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> a(n);

    int sum_si = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum_si += (s[i] - '0');
    }

    // maximum subarray sum
    int max_sum = 0;
    int current_sum = 0;
    for (int i = 0; i < n; i++) {
        current_sum += a[i];
        if (current_sum < 0) {
            current_sum = 0;
        }
        max_sum = max(max_sum, current_sum);
    }

    if (sum_si == n) {
        if (max_sum == k) {
            cout << "YES" << endl;
            for (int e : a) {
                cout << e << " ";
            }
            cout << endl;
        } else {
            cout << "NO" << endl;
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            a[i] = -MOD;
        }
    }

    // maximum subarray sum
    max_sum = 0;
    current_sum = 0;
    for (int i = 0; i < n; i++) {
        current_sum += a[i];
        if (current_sum < 0) {
            current_sum = 0;
        }
        max_sum = max(max_sum, current_sum);
    }

    if (max_sum > k) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        int pos = -1;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                pos = i;
                break;
            }
        }

        // maximum suffix_sum until pos
        int max_sum_until_pos = 0;
        int current_sum_until_pos = 0;
        for (int i = pos - 1; i >= 0; i--) {
            current_sum_until_pos += a[i];
            max_sum_until_pos = max(max_sum_until_pos, current_sum_until_pos);
        }

        // maximum prefix_sum after pos
        int max_sum_after_pos = 0;
        int current_sum_after_pos = 0;
        for (int i = pos + 1; i < n; i++) {
            current_sum_after_pos += a[i];
            max_sum_after_pos = max(max_sum_after_pos, current_sum_after_pos);
        }

        a[pos] = k - max_sum_after_pos - max_sum_until_pos;

        for (int e : a) {
            cout << e << " ";
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