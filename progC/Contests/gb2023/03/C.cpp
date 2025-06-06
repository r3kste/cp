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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    while (k > 0) {
        if (s.find_first_not_of(s[0]) == string::npos) {
            while (k--) {
                s += s[0];
            }

            cout << s;
            return 0;
        }

        string rs = s;
        reverse(all(rs));

        if (rs == s) {
            s += s.back();
            k--;
        }

        if (k > 0) {
            s = s.substr(0, s.size() / 2);
        }

        k--;
    }

    cout << s;
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