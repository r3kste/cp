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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    int S = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        S += a[i];
    }

    // int max_elem = *max_element(a.begin(), a.end());
    // int min_elem = *min_element(a.begin(), a.end());
    sort(a.begin(), a.end());
    a.back()--;
    sort(a.begin(), a.end());

    if (a.back() - a[0] > k) {
        cout << "Jerry" << endl;
    } else {
        if (S % 2 == 0) {
            cout << "Jerry" << endl;
        } else {
            cout << "Tom" << endl;
        }
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