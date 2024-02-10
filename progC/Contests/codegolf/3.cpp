#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, q;
    cin >> n;
    int a[n], ps[n];

    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a, a + n);
    ps[0] = a[0];

    for(int i = 1; i < n; i++) {
        ps[i] = ps[i - 1] + a[i];
    }

    cin >> q;

    while(q--) {
        int x;
        cin >> x;
        cout << 86400 - ps[x - 1] << '\n';
    }
}