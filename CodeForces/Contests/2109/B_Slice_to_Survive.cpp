#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

// f(n,m) = number of cuts required to end the game
int f(int n, int m)
{
    if (n == 1)
    {
        if (m == 1)
        {
            return 0;
        }
        return 1 + f(1, (m + 1) / 2);
    }
    return 1 + f((n + 1) / 2, m);
}

void test()
{
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    int row_rem = 1 + min(a - 1, n - a);
    int col_rem = 1 + min(b - 1, m - b);

    int ans = 1 + min(f(row_rem, m),
                      f(n, col_rem));

    cout << ans << "\n";
}

int32_t main()
{
    fastio;
    int t = 1;
    cin >> t;

    while (t--)
    {
        test();
    }

    return 0;
}