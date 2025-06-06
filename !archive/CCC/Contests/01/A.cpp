#include <bits/stdc++.h>

using namespace std;

#define to(i, a, b, c) for (int(i) = (a); (i) < b; (i) += c)
#define fro(i, a, b, c) for (int(i) = (b) - 1; (i) >= (a); (i) -= c)

#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

int solve();

int main() {
    fastio;
    int t = 1;

    if (false) {
        cin >> t;
    }

    while (t--) {
        solve();
        cout << "\n";
    }
}

int solve() {
    fastio;
    int a, b;
    cin >> a >> b;
    int n;
    cin >> n;
    int o = 0;
    to(i, 1, n + 1, 1) {
        if (i % 2 == 0) {
            o -= b;
        } else {
            o += a;
        }
    }

    cout << o;
    return 0;
}