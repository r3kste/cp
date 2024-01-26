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
    int n, k, p, q;
    in2(n, k);
    in2(p, q);
    vi a(n);
    vin (a);
    vi b(n);
    vin (b);
    vi d_rainfall(n + 1);

    while(k--) {
        int l, r, x;
        in3(l, r, x);
        l--;
        r--;
        d_rainfall[l] += x;
        d_rainfall[r + 1] -= x;
    }

    vi rainfall(n);
    rainfall[0] = d_rainfall[0];

    for (int i = 1; i < n; i++) {
        rainfall[i] = rainfall[i - 1] + d_rainfall[i];
    }

    ll could_give_to = 0;
    ll could_take_from = 0;
    ll havetogiveto = 0;
    ll havetotakefrom = 0;

    for (int i = 0; i < n; i++) {
        if (rainfall[i] > a[i]) {
            could_take_from += rainfall[i] - a[i];
        }

        if (rainfall[i] < a[i]) {
            havetogiveto += a[i] - rainfall[i];
        }

        if (rainfall[i] < b[i]) {
            could_give_to += b[i] - rainfall[i];
        }

        if (rainfall[i] > b[i]) {
            havetotakefrom += rainfall[i] - b[i];
        }
    }

    if(havetogiveto <= could_take_from + havetotakefrom && havetotakefrom <= could_give_to + havetogiveto) {
        o((havetogiveto + havetotakefrom) * (p + q));
    } else {
        o(-1);
    }

    br;
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
