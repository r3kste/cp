#include <bits/stdc++.h>

using namespace std;

#define MOD (LL)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

#define endl "\n"
#define yesno(a) cout << ((a) ? "Yes" : "No");

#define F first
#define S second
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

typedef long long int ll;
typedef unsigned long long int LL;
typedef pair<int, int> ii;

typedef vector<int> vi;
typedef vector<pair<int, int >> vii;
typedef vector<long long int> vll;

int getmaxdigit(ll n) {
    auto m = to_string(n);
    int max = 0;

    for (auto i : m) {
        if (i > max) {
            max = i;
        }
    }

    max -= 48;
    return max;
}

int solve() {
    fastio;
    ll n;
    cin >> n;
    ll ans = 0;

    while (n > 0) {
        ans++;
        n -= getmaxdigit(n);
    }

    cout << ans;
    return 0;
}

int main() {
    fastio;
    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
        cout << "\n";
    }
}