#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

// returns X^n
ll power(ll X, ll n) {
    ll res = 1;
    ll t = X;

    while (n > 0) {
        if (n % 2 == 1) {
            res = (res * t);
        }

        n /= 2;
        t = (t * t);
    }

    return res;
}

int main() {
    ll X, n;
    cout << "Enter the value of X: ";
    cin >> X;
    cout << "Enter the value of n: ";
    cin >> n;
    cout << "The value of X^n is: ";
    cout << power(X, n) << "\n";
    return 0;
}