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

#define oyes out("Yes", "\n")
#define ono out("No", "\n")

int solve() {
    fastio int n;
    in(n)
        vll a(n);
    vin(a);
    vi parity(n);

    for (int i = 0; i < n; i++) {
        if (a[i] % 2) {
            a[i] += (a[i] % 10);
        }
    }

    bool flag = true;
    ll temp;

    for (int i = 0; i < n; i++) {
        ll last = a[i] % 10;

        if (last == 0) {
            if (flag) {
                temp = a[i];
                flag = false;
                continue;
            } else {
                if (temp != a[i]) {
                    ono;
                    return 0;
                } else {
                    continue;
                }
            }
        }

        while (last != 2) {
            a[i] += (a[i] % 10);
            last = a[i] % 10;
        }
    }

    for (int i = 0; i < n; i++) {
        a[i] %= 20;
    }

    map<ll, ll> freq;

    for (int i = 0; i < n; i++) {
        freq[a[i]]++;
    }

    if (sz(freq) == 1) {
        oyes;
    } else {
        ono;
    }

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
