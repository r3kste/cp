#include<bits/stdc++.h>
using namespace std;
#define o 1000
char g[o][o];

void f (int i, int j) {
    if (i >= 0 && i < o && j >= 0 && j < o) {
        g[i][j] = 'p';

        if (g[i][j + 1] == '.') {
            f (i, j + 1);
        }

        if (g[i][j - 1] == '.') {
            f (i, j - 1);
        }

        if (g[i + 1][j] == '.') {
            f (i + 1, j);
        }

        if (g[i - 1][j] == '.') {
            f (i - 1, j);
        }
    }
}

int main() {
    int n, m, x, y;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];

            if(g[i][j] == 'O') {
                x = i;
                y = j;
                g[i][j] = 'p';
            }
        }
    }

    f(x, y);

    for(int j = 0; j < m; j++) {
        if(g[0][j] == 'p' || g[n - 1][j] == 'p' || g[j][0] == 'p' || g[j][m - 1] == 'p') {
            cout << "YES\n";
            cout << n + m - 12;
            return 0;
        }
    }

    cout << "NO";
}