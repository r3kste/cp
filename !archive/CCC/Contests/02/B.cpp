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

    if (true) {
        cin >> t;
    }

    while (t--) {
        solve();
        cout << "\n";
    }
}

int solve() {
    fastio;
    ll n, m;
    cin >> n >> m;
    // vi a(n);
    ll max = 0;
    ll mi = -1;
    to (i, 0, m, i + 1) {
        ll a, q;
        cin >> a >> q;
        ll no = n / q;
        no = min (a, no);

        if (no > max) {
            max = no;
            mi = i + 1;
        }
    }
    cout << mi;
    return 0;
}