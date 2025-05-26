#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
// #define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

void test()
{
    int n, ret;
    cin >> n;
    cout << "digit" << endl;
    cin >> ret;
    cout << "digit" << endl;
    cin >> ret;

    int mid = 8;

    cout << "add " << -mid << endl;
    cin >> ret;
    mid /= 2;

    // [1,8]

    cout << "add " << -mid << endl;
    cin >> ret;
    mid /= 2;

    // [1,4]

    cout << "add " << -mid << endl;
    cin >> ret;
    mid /= 2;

    // [1, 2]

    cout << "add " << -mid << endl;
    cin >> ret;
    mid /= 2;

    // [1]

    cout << "mul " << n << endl;
    cin >> ret;

    cout << "!" << endl;
    cin >> ret;
}

int32_t main()
{
    // fastio;
    int t = 1;
    cin >> t;

    while (t--)
    {
        test();
    }

    return 0;
}