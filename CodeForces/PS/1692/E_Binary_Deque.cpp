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

ll query(int l, int r, vector<ll>& ps) {
    return ps[r] - (l ? ps[l - 1] : 0);
}

int solve() {
    fastio
    ll n, s;
    in2(n, s);
    vi a(n);
    vin (a);
    vll ps(n);
    ps[0] = a[0];

    for(int i = 1; i < n; ++i) {
        ps[i] = ps[i - 1] + a[i];
    }

    ll ans = LLONG_MAX;

    for(int i = 0; i < n; i++) {
        int l = i, r = n - 1, pos = -1;

        while(l <= r) {
            int mid = l + (r - l) / 2;

            if(query(i, mid, ps) <= s) {
                pos = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if(pos == -1 || query(i, pos, ps) != s) {
            continue;
        }

        ans = min(ans, n - (pos - i + 1));
    }

    out((ans == LLONG_MAX ? -1 : ans), "\n");
    return 0;
}

int main() {
    fastio;
    int t = 1;
    in (t);

    while (t--) {
        solve();
    }
}