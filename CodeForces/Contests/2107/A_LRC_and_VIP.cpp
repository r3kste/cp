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
    vector<int> odd;
    vector<int> even;
    set<int> uniq;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        uniq.insert(a[i]);
        if (a[i] % 2 == 0) {
            even.push_back(a[i]);
        } else {
            odd.push_back(a[i]);
        }
    }

    // if (even.size() == 0 || odd.size() == 0) {
        if (uniq.size() == 1) {
            cout << "NO" << endl;
        } else {
            int max_elem = *max_element(a.begin(), a.end());
            cout << "YES" << endl;
            for (int i = 0; i < n; i++) {
                if (a[i] == max_elem) {
                    cout << 2 << " ";
                } else {
                    cout << 1 << " ";
                }
            }
            cout << endl;
        }
    // } else {
    //     cout << "YES" << endl;
    //     for (int i = 0; i < n; i++) {
    //         if (a[i] % 2 == 0) {
    //             cout << 2 << " ";
    //         } else {
    //             cout << 1 << " ";
    //         }
    //     }
    //     cout << endl;
    // }
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