#include <bits/stdc++.h>

using namespace std;

#define nmod(m) n % m == 0

#define to(i, a, b, c) for (int(i) = (a); (i) < (b); (i) = (c))
#define fro(i, a, b, c) for (int(i) = (b)-1; (i) >= (a); (i) = (c))

#define MOD (LL)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

typedef long long int ll;
typedef unsigned long long int LL;
typedef pair<int, int> ii;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef vector<unsigned long long int> vLL;

int solve();

int main() {
    fastio;
    int t = 1;

    if (false) {
        cin >> t;
    }

    while (t--) {
        solve();
        cout << "\n";
    }
}

int solve() {
    fastio;
    int n;
    cin >> n;
    ll min = MOD;
    ll s = 0;
    to(i, 0, n, i + 1) {
        ll temp;
        cin >> temp;

        if (temp % 2 == 0) {
            temp = temp - 1;
        }

        if (temp < min) {
            min = temp;
        }

        s += temp;
    }

    if (n % 2 == 0) {
        s -= min;
    }

    cout << s;
    return 0;
}
