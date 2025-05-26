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
    cin.tie(nullptr);

#define F first
#define S second
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)(a).size())

#define rep(_, n) \
    int _;        \
    for (_ = 0; _ < n; _++)

#define in(_) cin >> _;
#define in2(_0, _1) cin >> _0 >> _1;
#define in3(_0, _1, _2) cin >> _0 >> _1 >> _2;
#define vin(a)          \
    {                   \
        rep(_, sz(a)) { \
            in(a[_])    \
        }               \
    }
#define vvin(r, c)                \
    {                             \
        rep(__, r) {              \
            rep(_, c) {           \
                in(matrix[__][_]) \
            }                     \
        }                         \
    }
#define br cout << "\n";
#define out(_, __) cout << _ << __;
#define o(_) out(_, " ")
#define vout(__)        \
    for (auto _ : __) { \
        o(_)            \
    }                   \
    br
#define vvout(___)        \
    for (auto __ : ___) { \
        vout(__);         \
    }

#define oyes out("YES", "\n")
#define ono out("NO", "\n")

bool valid(ll max_water, vi &a, vi &ps, ll height, int n) {
    int pos = lower_bound(all(a), height) - a.begin();
    pos = min(pos, n - 1);
    ll non_empty = ps[pos];
    ll empty = height * (pos + 1) - non_empty;
    return empty <= max_water;
}

int solve() {
    fastio int n;
    ll max_water;
    in(n)
        in(max_water)
            vi a(n);
    vin(a);
    sort(all(a));
    vi ps(n, 0);
    ps[0] = a[0];

    for (int i = 1; i < n; i++) {
        ps[i] = ps[i - 1] + a[i];
    }

    ll sum = 0;

    for (int i = 0; i < n; i++) {
        sum -= a[i];
    }

    ll l = 1;
    ll r = MOD * 10;
    int n_iter = 100;

    while (l < r) {
        ll m = l + (r - l + 1) / 2;

        if (valid(max_water, a, ps, m, n)) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    out(l, "\n");
    return 0;
}

int main() {
    fastio;
    int t = 1;
    in(t);

    while (t--) {
        solve();
    }
}
