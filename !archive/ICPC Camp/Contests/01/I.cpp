#include <bits/stdc++.h>
using namespace std;

#define nmod(m) n % m == 0

#define to(i, a, b, c) for (int(i) = (a); (i) < (b); (i) = (c))
#define fro(i, a, b, c) for (int(i) = (b)-1; (i) >= (a); (i) = (c))

#define MOD (LL)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

typedef long long int ll;
typedef unsigned long long int LL;
typedef pair<int, int> ii;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef vector<unsigned long long int> vLL;

int solve();

int main()
{
    fastio;

    int t = 1;
    if (true)
        cin >> t;

    while (t--)
    {
        solve();
        cout << "\n";
    }
}

int solve()
{
    fastio;

    bool dot = false;
    string a;
    cin >> a;

    to(i, 1, 3, i + 1)
    {
        if (a[i] == '.')
        {
            dot = true;
        }
        else if (a[i] == '/')
        {
            break;
        }
    }

    a = a + ".";

    string build = "";
    int k[3] = {2, 2, 4};
    int c = 0;
    string date = "", month = "", year = "";

    to(i, 0, a.size() + 1, i + 1)
    {
        if (a[i] == '.' || a[i] == '/')
        {
            if (build.length() != k[c])
            {
                string st = "";
                to(j, 0, k[c] - build.length(), j + 1)
                {
                    st.append("0");
                }
                st.append(build);
                build = st;
            }
            if (dot)
            {
                if (c == 0)
                {
                    date = build;
                }
                else if (c == 1)
                {
                    month = build;
                }
                else
                {
                    year = build;
                }
            }
            else
            {
                if (c == 0)
                {
                    month = build;
                }
                else if (c == 1)
                {
                    date = build;
                }
                else
                {
                    year = build;
                }
            }
            c++;
            build = "";
        }
        else
        {
            build = build + "" + a[i];
        }
    }

    cout << date << "." << month << "." << year;
    cout << " " << month << "/" << date << "/" << year;

    return 0;
}
