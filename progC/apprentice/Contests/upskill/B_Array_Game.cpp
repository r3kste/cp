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

int solve() {
    fastio
    int n, k;
    in2(n, k);
    vll a(n);
    vin (a);

    if (k >= 3) {
        o(0)br;
    } else {
        sort(all(a));
        vector<vector<ll>> diff(n, vector<ll>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                diff[i][j] = abs(a[j] - a[i]);
                diff[j][i] = diff[i][j];
            }
        }

        if (k == 1) {
            ll ans = a[0];

            for (int i = 1; i < n; i++) {
                ans = min(ans, a[i] - a[i - 1]);
            }

            o(ans)br;
        } else if (k == 2) {
            sort(all(a));

            for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                    diff[i][j] = abs(a[j] - a[i]);
                    diff[j][i] = diff[i][j];
                }
            }

            ll ans = a[0];

            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    ll val = diff[i][j];
                    ans = min(ans, val);
                    int pos = lower_bound(all(a), val) - a.begin();
                    ans = min(ans, abs(a[min(n - 1, pos)] - val));
                    ans = min(ans, abs(a[max(0, pos - 1)] - val));
                }
            }

            o(ans)br;
        }
    }

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
