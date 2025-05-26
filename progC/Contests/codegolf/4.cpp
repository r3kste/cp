#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, m, k = 1, c = 0;
        cin >> n >> m;
        int a[n + m][m + n];
        int i = 0, j = 0;

        while (true) {
            a[i][j] = k;

            if (i < n && j < m) {
                k++;
            }

            if (i == n - 1 && j == m - 1) {
                break;
            }

            if (i == 0) {
                i = j + 1;

                if (j + 1 >= n) {
                    i = n - 1;
                    c++;
                }

                j = c;
            } else {
                i--;
                j++;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << a[i][j] << " ";
            }

            cout << '\n';
        }
    }
}