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

int powofa(ll n, int a) {
    int cnt = 0;

    while (n > 0) {
        if (n % a != 0) {
            break;
        }

        n /= a;
        cnt++;
    }

    return cnt;
}
int solve() {
    fastio
    ll n, m;
    in2 (n, m);
    int cnt2 = powofa(n, 2);
    int cnt5 = powofa(n, 5);
    ll k = 1;

    while(cnt2 < cnt5 && k * 2 <= m) {
        cnt2++;
        k *= 2;
    }

    while (cnt5 < cnt2 && k * 5 <= m) {
        cnt5++;
        k *= 5;
    }

    while (k * 10 <= m) {
        k *= 10;
    }

    if (k == 1) {
        k = m;
    } else {
        k *= m / k;
    }

    out(n * k, "\n");
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