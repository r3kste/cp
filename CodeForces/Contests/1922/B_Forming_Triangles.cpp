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

ll nc3(ll n) {
    return ((unsigned long long int)(n * (n - 1) * (n - 2))) / 6;
}

ll nc2(ll n) {
    return ((unsigned long long int)(n * (n - 1))) / 2;
}

int solve() {
    fastio;
    ll n;
    in(n);
    vi a(n);
    vin(a);
    sort(all(a));
    map<ll, ll> freq;

    for (ll e : a) {
        freq[e]++;
    }

    ll ans = 0;

    for (auto e : freq) {
        ll no = e.F;
        ll count = e.S;

        if (count < 2) {
            continue;
        } else if (count == 2) {
            ll m = lower_bound(all(a), no) - begin(a);
            ans += (m);
        } else if (count >= 3) {
            ll m = lower_bound(all(a), no) - begin(a);
            ans += nc3(count) + nc2(count) * m;
        }
    }

    o(ans)
        br return 0;
}

int main() {
    fastio;
    int t = 1;
    in(t);

    while (t--) {
        solve();
    }
}
