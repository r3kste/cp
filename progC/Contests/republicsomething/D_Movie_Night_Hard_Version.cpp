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

int solve() {
    fastio
        ll n,
        k;
    in2(n, k)
        vector<pair<ll, int>>
            a;
    for (int i = 0; i < n; i++) {
        int x;
        in(x)
            a.push_back(mp(x, i + 1));
    }

    sort(all(a));
    vector<pair<ll, int>> b;

    for (int i = 0; i < n; i++) {
        b.pb(mp(a[i].F - k * a[i].S, a[i].S));
    }
    sort(all(b));
    ll score = 0;
    score += b.back().F;

    if (b.back().S == a.back().S) {
        score += max(b[sz(b) - 2].F, a[sz(a) - 2].F);
    } else {
        score += a.back().F;
    }
    ll score2 = 0;
    score2 += a.back().F;

    if (a.back().S == b.back().S) {
        score2 += b[sz(b) - 2].F;
    } else {
        score2 += b.back().F;
    }
    o(max(score, score2)) br;
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
