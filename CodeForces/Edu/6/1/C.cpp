#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;

typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<bool> vb;
typedef vector<ll> vll;
typedef vector<vi> vvi;

#define MOD (ll)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

#define F first
#define S second
#define mp make_pair
#define pb(__, _) __.push_back(_);
#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)(a).size())

#define rep(_, n) \
    int _;        \
    for (_ = 0; _ < n; _++)

#define in(_) cin >> _;
#define in2(_0, _1) cin >> _0 >> _1;
#define in3(_0, _1, _2) cin >> _0 >> _1 >> _2;
#define vin(n)   \
    rep(_, n) {  \
        in(a[_]) \
    }
#define vvin(r, c)            \
    rep(__, r) {              \
        rep(_, c) {           \
            in(matrix[__][_]) \
        }                     \
    }
#define br cout << "\n";
#define out(_, __) cout << _ << __;
#define o(_) out(_, " ")
#define vout(__)       \
    for (int _ : __) { \
        o(_)           \
    }                  \
    br
#define vvout(___)      \
    for (vi __ : ___) { \
        vout(__);       \
    }

#define oyes out("YES", "\n")
#define ono out("NO", "\n")

int solve() {
    fastio;
    int n, k;
    in2(n, k);
    n += 2;
    vi a(n);
    a[0] = INT32_MIN;
    rep(_, n - 2) in(a[_ + 1]);
    a[n - 1] = INT32_MAX;
    reverse(all(a));

    while (k--) {
        int x;
        in(x);
        /*Halving Binary Search*/
        // int l, r, m;
        // l = 0;
        // r = n - 1;
        // while (l < r - 1)
        // {
        //     m = (l + r) / 2;
        //     if (a[m] > x)
        //     {
        //         r = m;
        //     }
        //     else
        //     {
        //         l = m;
        //     }
        // }
        // o (n - 1 - l);
        /*Jumping Binary Search*/
        int ptr = 0;

        for (int jump = n / 2; jump >= 1; jump /= 2) {
            while (ptr + jump < n && a[ptr + jump] >= x) {
                ptr += jump;
            }
        }

        o(n - 1 - ptr);
    }

    br;
    return 0;
}

int main() {
    fastio;
    int t = 1;
    // in (t);

    while (t--) {
        solve();
    }
}