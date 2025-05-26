#include <bits/stdc++.h>
using namespace std;

#define int long long

void test() {
    int n;
    cin >> n;
    vector<pair<int, int>> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].first >> pts[i].second;
    }
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }

    vector<pair<int, int>> x_sorted, y_sorted;
    for (int i = 0; i < n; i++) {
        x_sorted.push_back({pts[i].first, i});
        y_sorted.push_back({pts[i].second, i});
    }
    sort(x_sorted.begin(), x_sorted.end());
    sort(y_sorted.begin(), y_sorted.end());

    set<int> candidates;
    for (int i = 0; i < min(2LL, n); i++) {
        candidates.insert(x_sorted[i].second);
        candidates.insert(x_sorted[n - 1 - i].second);
        candidates.insert(y_sorted[i].second);
        candidates.insert(y_sorted[n - 1 - i].second);
    }

    int ans = LLONG_MAX;
    for (auto candidate : candidates) {
        int min_x = LLONG_MAX, max_x = LLONG_MIN;
        int min_y = LLONG_MAX, max_y = LLONG_MIN;
        for (int i = 0; i < n; i++) {
            if (i == candidate) {
                continue;
            }
            min_x = min(min_x, pts[i].first);
            max_x = max(max_x, pts[i].first);
            min_y = min(min_y, pts[i].second);
            max_y = max(max_y, pts[i].second);
        }
        int len = max_x - min_x + 1;
        int wid = max_y - min_y + 1;
        int area = len * wid;
        if (area == n - 1) {
            area = min((len + 1) * wid, len * (wid + 1));
        }
        ans = min(ans, area);
    }
    cout << ans << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        test();
    return 0;
}