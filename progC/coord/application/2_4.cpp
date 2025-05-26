#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    typedef long long int ll;

    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        map<ll, ll> freq;

        for (int i = 0; i < n; i++) {
            cin >> a[i];
            freq[a[i]]++;
        }

        int q;
        cin >> q;

        while (q--) {
            ll x, y;
            cin >> x >> y;
            ll D = ll(x * x - 4 * y);

            if (D < 0) {
                cout << "0 ";
            } else if (D == 0) {
                ll p = x / 2;
                ll f = freq[p];
                ll res = f * (f - 1) / 2;
                cout << res << " ";
            } else {
                double sqrt_d = sqrt(D);
                ll int_sqrt_d = ll(ceil(sqrt_d));

                if ((ceil(sqrt_d) == floor(sqrt_d)) && (int_sqrt_d * int_sqrt_d == D)) {
                    ll p1 = (x + int_sqrt_d) / 2;
                    ll p2 = (x - int_sqrt_d) / 2;
                    ll f1 = freq[p1];
                    ll f2 = freq[p2];
                    ll res = f1 * f2;
                    cout << res << " ";
                } else {
                    cout << "0 ";
                }
            }
        }

        cout << "\n";
    }
}