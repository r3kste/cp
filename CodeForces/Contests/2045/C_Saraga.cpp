#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define INF LLONG_MAX
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

int find_first(string &s, char c) {
    for (int i = 1; i < s.size(); i++)
        if (s[i] == c) {
            return i;
        }

    return -1;
}

int find_last(string &s, char c) {
    for (int i = s.size() - 2; i >= 0; i--)
        if (s[i] == c) {
            return i;
        }

    return -1;
}

void test() {
    string a, b;
    cin >> a >> b;
    int min_length = INF;
    char min_length_c = ' ';

    for (char c = 'a'; c <= 'z'; c++) {
        int a_pos = find_first(a, c);
        int b_pos = find_last(b, c);

        if (a_pos == -1 || b_pos == -1) {
            continue;
        }

        int length = a_pos + (b.size() - b_pos);

        if (length < min_length) {
            min_length = length;
            min_length_c = c;
        }
    }

    if (min_length == INF) {
        cout << -1 << endl;
        return;
    }

    int a_pos = find_first(a, min_length_c);
    int b_pos = find_last(b, min_length_c);
    string res = a.substr(0, a_pos + 1) + b.substr(b_pos + 1);
    cout << res << endl;
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