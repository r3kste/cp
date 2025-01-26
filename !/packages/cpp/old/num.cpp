#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

bool isPrime(ll n) {
    if (n == 2 || n == 3) {
        return true;
    } else if (n % 2 == 0 || n % 3 == 0 || n < 2) {
        return false;
    } else {
        ll sqrtN = ll(sqrt(n));

        for (ll i = 5; i < sqrtN; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }

        return true;
    }
}

ll power(ll x, ll y, ll mod) {
    ll res = 1;
    x %= mod;

    while (y > 0) {
        if (y & 1) {
            res = (res * x) % mod;
        }

        y >>= 1;
        x = (x * x) % mod;
    }

    return res;
}

ll inv(ll n, ll mod) {
    return power(n, mod - 2, mod);
}

ll mul(ll x, ll y, ll mod) {
    return ((x % mod) * (y % mod)) % mod;
}

ll div(ll x, ll y, ll mod) {
    return mul(x, inv(y, mod), mod);
}

ll ncr(ll n, ll r, ll mod) {
    if (n < r) {
        return 0;
    }

    if (r == 0) {
        return 1;
    }

    if (n - r < r) {
        return ncr(n, n - r, mod);
    }

    ll res = 1;

    for (ll i = r; i > 0; i--) {
        res = div(mul(res, n - i + 1, mod), i, mod);
    }

    return res;
}

vector<ll> factors(ll n) {
    vector<ll> factors;
    const ll sqrtN = ll(sqrt(n));

    for (int i = 1; i <= sqrtN; ++i) {
        if (n % i == 0) {
            factors.push_back(i);
            factors.push_back(n / i);
        }
    }

    return factors;
}

int main() {
}
