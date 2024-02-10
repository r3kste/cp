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

int solve(int t) {
    fastio
    int n, x, y;
    in3(n, x, y);
    string a, b;
    in2(a, b);
    int changes = 0;
    vi tobefixed;

    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            changes++;
            tobefixed.pb(i);
        }
    }

    if (changes % 2) {
        out(-1, "\n");
        return 0;
    }

    ll ans = 0;

    while (!tobefixed.empty()) {
        int i = 0;
        int l = tobefixed[i];
        int r;

        if (i + 2 < sz(tobefixed)) {
            r = tobefixed[i + 2];
            tobefixed.erase(tobefixed.begin() + i + 2);
        } else {
            r = tobefixed[i + 1];
            tobefixed.erase(tobefixed.begin() + i + 1);
        }

        tobefixed.erase(tobefixed.begin() + i);

        if (r - l == 1) {
            if (2 * y < x) {
                if (r + 2 < n || l - 2 >= 0 || (l + 2) <= (r - 2)) {
                    ans += y + y;
                } else {
                    ans += x;
                }
            } else {
                ans += x;
            }
        } else {
            ans += y;
        }
    }

    out(ans, "\n");
    return 0;
}

int main() {
    fastio;
    int t = 1;
    in (t);

    for (int i = 1; i <= t; i++) {
        solve(i);
    }
}
