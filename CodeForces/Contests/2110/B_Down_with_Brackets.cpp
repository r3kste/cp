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
    string s;
    cin >> s;

    int no_of_peaks = 0;
    int no_of_val = 0;
    int cnt = 0;

    int n = s.size();
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '(') {
            cnt++;
        } else {
            cnt--;
        }
        a[i] = cnt;
    }

    if (a[1] < a[0] && a[0] > 0) {
        no_of_peaks++;
    }
    for (int i = 2; i < n; i++) {
        if (a[i] < a[i - 1] && a[i - 1] > a[i - 2]) {
            no_of_peaks++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            no_of_val++;
        }
    }

    if (no_of_val == 1) {
        cout << "NO";
    } else {
        cout << "YES";
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