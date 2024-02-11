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

bool valid(vll &a, int k) {
    vi b(sz(a) + 1);

    for (int i = 1; i <= sz(a); i++) {
        b[i] = max(1, sz(a) / i - 1);
    }

    vi cb = b;
    ll c = 0;
    ll ans = 0;

    for (int i = 0; i < sz(a) - 1; i++) {
        if (a[i + 1] - a[i] <= 0 || a[i + 1] - a[i] > sz(a)) {
            c = 0;
            b = cb;
            continue;
        }

        b[a[i + 1] - a[i]]--;
        c++;
        ans = max(ans, c);

        if (b[a[i + 1] - a[i]] < 0) {
            c = 0;
            b = cb;
        }
    }

    o(ans)br
    return ans >= k;
}
int solve() {
    fastio
    ll n;
    in (n)
    vll a(n);
    vin (a);
    sort(all(a));
    int ans = 1;
    int prev = 0;
    set<int> ttt (all(a));
    vi aa (all(ttt));

    for (int i = 0; i < sz(aa); i++) {
        while (aa[i] - aa[prev] >= n) {
            prev++;
        }

        ans = max(ans, i - prev + 1);
    }

    o(ans)br
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