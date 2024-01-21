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
    vll a (n, 0);
    vll ps (n + 1, 0);
    ll amax = -MOD * MOD;
    ll amin = MOD * MOD;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ps[i + 1] = ps[i] + a[i];

        if (a[i] > amax) {
            amax = a[i];
        }

        if (a[i] < amin) {
            amin = a[i];
        }
    }

    ll ans = amax - amin;

    for (int k = 2; k <= sqrt (n); k++) {
        if (n % k == 0) {
            ll max = -MOD * MOD;
            ll min = MOD * MOD;

            for (int i = 0; i <= n - k; i += k) {
                ll temp = ps[i + k] - ps[i];

                if (temp > max) {
                    max = temp;
                }

                if (temp < min) {
                    min = temp;
                }

                if (max - min > ans) {
                    ans = max - min;
                }
            }

            int ck = k;
            k = n / k;
            max = -MOD * MOD;
            min = MOD * MOD;

            for (int i = 0; i <= n - k; i += k) {
                ll temp = ps[i + k] - ps[i];

                if (temp > max) {
                    max = temp;
                }

                if (temp < min) {
                    min = temp;
                }

                if (max - min > ans) {
                    ans = max - min;
                }
            }

            k = ck;
        }
    }

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
