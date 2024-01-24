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
#define sz(a) ((int) (a).size())

#define rep(_, n) int _; for(_ = 0; _ < n; _++)

#define in(_) cin >> _;
#define in2(_0, _1) cin >> _0 >> _1;
#define in3(_0, _1, _2) cin >> _0 >> _1 >> _2;
#define vin(a) { rep (_, sz (a)) { in (a[_]) }}
#define vvin(r, c) { rep(__,r) { rep(_,c) { in (matrix[__][_]) } } }
#define br cout << "\n";
#define out(_, __) cout << _ << __;
#define o(_) out(_, " ")
#define vout(__) for (auto _ : __) { o (_) } br
#define vvout(___)  for (auto __ : ___) { vout (__); }

#define oyes out("YES","\n")
#define ono out("NO", "\n")

int solve() {
    fastio
    ll n, m, k;
    in3(n, m, k);
    vll a(n);
    vin (a);
    vll d_op(m + 1, 0);
    vector<pair<pair<ll, ll>, ll>> q(m);

    for (ll i = 0; i < m; i++) {
        ll l, r, d;
        in3(l, r, d);
        l--;
        r--;
        q[i] = mp(mp(l, r), d);
    }

    while (k--) {
        ll l, r;
        in2(l, r);
        l--;
        r--;
        d_op[l]++;
        d_op[r + 1]--;
    }

    vll n_op(m, 0);
    n_op[0] = d_op[0];

    for (ll i = 1; i < m; i++) {
        n_op[i] = n_op[i - 1] + d_op[i];
    }

    vll d_arr(n + 1, 0);

    for (ll i = 0; i < m; i++) {
        ll l = q[i].F.F;
        ll r = q[i].F.S;
        ll d = q[i].S;
        d *= n_op[i];
        d_arr[l] += d;
        d_arr[r + 1] -= d;
    }

    vll ps(n, 0);
    ps[0] = d_arr[0];

    for (ll i = 1; i < n; i++) {
        ps[i] = ps[i - 1] + d_arr[i];
    }

    for (ll i = 0; i < n; i++) {
        o(ps[i] + a[i]);
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
