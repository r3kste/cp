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

bool valid(vll &ps, ll m, ll time) {
    for (int i = 0; i < sz(ps); i++) {
        int j = i + m;

        if (j >= sz(ps)) {
            break;
        }

        if (ps[j] - ps[i] <= time) {
            return true;
        }
    }

    return false;
}

int solve() {
    fastio
        ll n,
        time;
    in2(n, time);
    vi a(n);
    vin(a);
    vll ps(n + 1);

    for (int i = 0; i < n; i++) {
        ps[i + 1] = ps[i] + a[i];
    }

    ll l = 0, r = n, m;

    while (l < r) {
        m = l + (r - l + 2) / 2;

        if (valid(ps, m, time)) {
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
    // in (t);

    while (t--) {
        solve();
    }
}
