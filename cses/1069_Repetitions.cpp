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
    int longest = 1;

    for (int i = 0; i < s.size(); i++) {
        int count = 1;

        while (i + 1 < s.size() && s[i] == s[i + 1]) {
            i++;
            count++;
        }

        longest = max(longest, count);
    }

    cout << longest << endl;
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