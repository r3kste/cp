#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef long long int lll;

template<typename T>
struct matrix {
    vector<vector<T>> mat;
    int rows, cols;
    int order{};

    matrix(int no_of_rows, int no_of_cols) {
        rows = no_of_rows;
        cols = no_of_cols;

        if (rows == cols) {
            order = rows;
        } else {
            order = -1;
        }

        mat = vector<vector<T>>(no_of_rows, vector<T>(no_of_cols, T(0)));
    }

    explicit matrix(int order) {
        rows = cols = this->order = order;
        mat = vector<vector<T>>(order, vector<T>(order, T(0)));
    }
};

matrix<lll> mul(matrix<lll> a, matrix<lll> b, ll m) {
    matrix<lll> res(a.rows, b.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            for (int k = 0; k < b.rows; k++) {
                res.mat[i][j] += a.mat[i][k] * b.mat[k][j];
                res.mat[i][j] %= m;
            }
        }
    }

    return res;
}

matrix<lll> pow(matrix<lll> a, ll n, ll m) {
    matrix<lll> res(a.order, a.rows);

    for (int i = 0; i < a.rows; i++) {
        res.mat[i][i] = 1;
    }

    while (n) {
        if (n & 1) {
            res = mul(res, a, m);
        }

        n >>= 1;
        a = mul(a, a, m);
    }

    return res;
}

int solve() {
    int n;
    cin >> n;
    return 0;
}

int main() {
    int t = 1;
    cin >> t;

    while (t--) {
        solve();
        cout << "\n";
    }
}
