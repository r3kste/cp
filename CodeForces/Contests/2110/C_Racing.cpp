#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

// true if there is atleast one common
bool isValid(int l, int r, pair<int, int> bounds)
{
    return !(l > bounds.second || r < bounds.first);
}

void test()
{
    int n;
    cin >> n;
    vector<int> d(n);

    for (int i = 0; i < n; i++)
    {
        cin >> d[i];
    }

    vector<pair<int, int>> bounds(n);
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        bounds[i] = {l, r};
    }
    vector<pair<int, int>> possible(n);
    int l = 0;
    int r = 0;
    for (int i = 0; i < n; i++)
    {
        if (d[i] == 1)
        {
            l++;
            r++;
        }
        else if (d[i] == -1)
        {
            r++;
        }
        l = max(l, bounds[i].first);
        r = min(r, bounds[i].second);
        if (l > r)
        {
            cout << -1 << endl;
            return;
        }
        possible[i] = {l, r};
    }

    int h = l;
    for (int i = n - 1; i >= 0; i--)
    {
        if (d[i] == 1)
        {
            h--;
        }
        else if (d[i] == -1)
        {
            int prev_ub;
            if (i > 0)
            {
                prev_ub = possible[i - 1].second;
            }
            else
            {
                prev_ub = 0;
            }

            if (h > prev_ub)
            {
                h--;
                d[i] = 1;
            }
            else
            {
                d[i] = 0;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << d[i] << " ";
    }
    cout << endl;
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