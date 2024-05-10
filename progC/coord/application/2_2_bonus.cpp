#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct matrix2 {
    ll mat[2][2];

    matrix2() {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }
    matrix2(ll a, ll b, ll c, ll d) {
        mat[0][0] = a;
        mat[0][1] = b;
        mat[1][0] = c;
        mat[1][1] = d;
    }

    matrix2 friend operator*(matrix2 &a, matrix2 &b) {
        matrix2 c;

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
                }
            }
        }

        return c;
    }

    matrix2 matpow(matrix2 a, ll n) {
        matrix2 res = {1, 0, 0, 1};
        matrix2 t = a;

        while (n) {
            if (n & 1) {
                res = res * t;
            }

            n >>= 1;
            t = t * t;
        }

        return res;
    }
};

int main() {
    matrix2 a = {1, 1, 1, 0};
    ll n;
    cout << "Enter the value of n: ";
    cin >> n;
    matrix2 b = a.matpow(a, n - 1);
    cout << "The nth Fibonacci number is: ";
    cout << b.mat[0][0] << "\n";
    return 0;
}