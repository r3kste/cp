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
typedef vector<pair<int, int>> vii;
typedef vector<long long int> vll;

int solve() {
    fastio;
    int n;
    cin >> n;
    vi x(n);

    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    vi z(n);

    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        z[i] = temp - x[i];
    }

    sort(all(z));
    int l = 0;
    int r = n - 1;
    int ans = 0;

    if (z[r] < 0) {
        cout << 0;
        return 0;
    }

    while (l < r) {
        if (z[r] + z[l] < 0) {
            l++;
        } else {
            ans++;
            l++;
            r--;
        }
    }

    // for (int i = 0; i < n; i++) {
    //     cout << z[i] << " ";
    // }
    cout << ans;
    return 0;
}

int main() {
    fastio;
    int t = 1;
    cin >> t;

    while (t--) {
        solve();
        cout << "\n";
    }
}
