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
    vi d_recipes(200001, 0);
    ll n, k, q;
    in3(n, k, q);

    for(int i = 0; i < n; i++) {
        int l, r;
        in2(l, r);
        l--;
        r--;
        d_recipes[l]++;
        d_recipes[r + 1]--;
    }

    vll recipes(200001, 0);
    recipes[0] = d_recipes[0];

    for(int i = 1; i < 200001; i++) {
        recipes[i] = recipes[i - 1] + d_recipes[i];
    }

    vb possible(200001, false);

    for (int i = 0; i < 200001; i++) {
        if (recipes[i] >= k) {
            possible[i] = true;
        }
    }

    vll ps_possible(200002, 0);
    ps_possible[0] = 0;

    for (int i = 1; i <= 200001; i++) {
        ps_possible[i] = ps_possible[i - 1] + possible[i - 1];
    }

    while(q--) {
        ll l, r;
        in2(l, r);
        o(ps_possible[r] - ps_possible[l - 1])br;
    }

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
