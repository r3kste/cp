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
        ll n;
    in(n)
        string s;
    in(s)
        vll a;
    vll ans(n + 1, 0);

    for (char c : s) {
        a.push_back(c - '0');
    }

    ll sum = 0;
    vll diff(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        sum += a[i - 1];
        ans[i] = sum;
        diff[i - 1] += ans[i] / 10;
        ans[i] %= 10;
    }

    if (ans[0] != 0) {
        out(ans[0], "");
    }

    vll act(n + 1, 0);

    for (int i = n; i >= 1; i--) {
        act[i] += ans[i] + diff[i];
        act[i - 1] += act[i] / 10;
        act[i] %= 10;
    }

    bool flag = true;

    for (int i = 0; i <= n; i++) {
        if (act[i] != 0) {
            flag = false;
        }

        if (flag && act[i] == 0) {
            continue;
        }

        out(act[i], "");
    }

    br;
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
