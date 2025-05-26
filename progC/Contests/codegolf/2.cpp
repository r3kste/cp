#include <bits/stdc++.h>
using namespace std;
int main() {
    string a;
    cin >> a;
    map<char, int> m;

    for (char c : a) {
        m[c]++;
        cout << m[c];
    }
}