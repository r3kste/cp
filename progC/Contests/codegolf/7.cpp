#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;

    while (t--) {
        int a, b, c, d, e, f;
        cin >> a >> b >> c >> d >> e >> f;
        double area = 0.5 * abs((a * (d - f) + c * (f - b) + e * (b - d)));

        if (area == 0) {
            cout << 1;
        } else {
            double side1 = (pow(c - a, 2) + pow(d - b, 2));
            double side2 = (pow(e - c, 2) + pow(f - d, 2));
            double side3 = (pow(a - e, 2) + pow(b - f, 2));

            if (side1 == side2 + side3 || side2 == side1 + side3 || side3 == side1 + side2) {
                cout << 2;
            } else {
                cout << 3;
            }
        }

        cout << '\n';
    }
}