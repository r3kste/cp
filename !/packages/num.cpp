#include <bits/stdc++.h>

using namespace std;

bool isPrime(long long int n) {
    if (n < 2) {
        return false;
    } else if (n == 2 || n == 3) {
        return true;
    } else if (n % 2 == 0 || n % 3 == 0) {
        return false;
    } else {
        double sqrtN = sqrt(n) + 1;

        for (long long int i = 5; i < sqrtN; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }

        return true;
    }
}

long long int power(long long int x, int y, long long int mod) {
    long long int res = 1;
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

long long int inv(long long int n, long long int mod) {
    return power(n, mod - 2, mod);
}

long long int mul(long long int x, long long int y, long long int mod) {
    return ((x % mod) * (y % mod)) % mod;
}

long long int div(long long int x, long long int y, long long int mod) {
    return mul(x, inv(y, mod), mod);
}

long long int ncr(long long int n, long long int r, long long int mod) {
    if (n < r) {
        return 0;
    }

    if (r == 0) {
        return 1;
    }

    if (n - r < r) {
        return ncr(n, n - r, mod);
    }

    long long int res = 1;

    for (int i = r; i > 0; i--) {
        res = div(mul(res, n - i + 1, mod), i, mod);
    }

    return res;
}

vector<long long int> factors(long long int n) {
    vector<long long int> factors;
    const int sqrtN = sqrt(n) + 1;

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
