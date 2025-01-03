#include <bits/stdc++.h>

using namespace std;

#define to(i, a, b, c) for (int(i) = (a); (i) < b; (i) += c)
#define fro(i, a, b, c) for (int(i) = (b)-1; (i) >= (a); (i) -= c)

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

    if (true) {
        cin >> t;
    }

    while (t--) {
        solve();
        cout << "\n";
    }
}

int solve() {
    fastio;
    int n, o = 0;
    cin >> n;
    vi a(n);
    to (i, 0, n, 1) {
        cin >> a[i];
    }

    sort(begin(a), end(a));
    to (i, 0, n / 2, 1) {
        o += (a[n - 1 - i] - a[i]);
    }

    cout << o;
    return 0;
}