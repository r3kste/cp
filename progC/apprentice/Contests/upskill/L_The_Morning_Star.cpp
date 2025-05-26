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

#define x F
#define y S
int solve() {
    fastio int n;
    in(n)
        vector<tuple<ll, ll, ll, ll>>
            dirs;
    for (int i = 0; i < n; i++) {
        int X, Y;
        in2(X, Y);
        dirs.pb({X, Y, X + Y, X - Y});
    }

    map<ll, ll> xdir, ydir, Idir, IIdir;

    for (auto &p : dirs) {
        xdir[get<0>(p)]++;
        ydir[get<1>(p)]++;
        Idir[get<2>(p)]++;
        IIdir[get<3>(p)]++;
    }
    dirs.clear();
    ll ans = 0;

    for (auto x : xdir) {
        ans += x.S * (x.S - 1) / 2;
    }
    for (auto y : ydir) {
        ans += y.S * (y.S - 1) / 2;
    }
    for (auto I : Idir) {
        ans += I.S * (I.S - 1) / 2;
    }
    for (auto II : IIdir) {
        ans += II.S * (II.S - 1) / 2;
    }
    o(ans * 2) br;
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
