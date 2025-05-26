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
    string s;
    cin >> s;

    map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }

    int zero = freq['0'];
    int one = freq['1'];

    int min_pairs = abs(zero - one) / 2;
    int max_pairs = zero / 2 + one / 2;

    int parity = min_pairs % 2;

    if (k % 2 != parity) {
        cout << "NO" << endl;
        return;
    }

    if (min_pairs > k || max_pairs < k) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
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