#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

struct Node {
    int id;
    int parent;
    char color;
    vector<int> children;
    int balance;

public:
    Node(int id, int parent, char color) {
        this->id = id;
        this->parent = parent;
        this->color = color;
        this->balance = color == 'W' ? 1 : -1;
    }
};

class Graph {
    int n;
    vector<Node> nodes;

public:
    Graph(int n, const vector<int>& parents, const string &colors) {
        this->n = n;
        nodes.push_back(Node(0, -1, colors[0]));

        for (int i = 1; i < n; i++) {
            nodes.push_back(Node(i, parents[i - 1] - 1, colors[i]));
        }

        for (int i = 1; i < n; i++) {
            nodes[nodes[i].parent].children.push_back(i);
        }
    }

    int answer() {
        dfs(0);
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (nodes[i].balance == 0) {
                ans++;
            }
        }

        return ans;
    }

private:
    void dfs(int node) {
        for (int child : nodes[node].children) {
            dfs(child);
            nodes[node].balance += nodes[child].balance;
        }
    }
};

int32_t main() {
    fastio;
    int t = 1;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);

        for (int i = 0; i < n - 1; i++) {
            cin >> a[i];
        }

        string s;
        cin >> s;
        Graph tree(n, a, s);
        cout << tree.answer() << endl;
    }
}