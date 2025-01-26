#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;

typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<bool> vb;
typedef vector<ll> vll;
typedef vector<vi> vvi;

#define MOD (ll)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

#define F first
#define S second
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) ((int) (a).size())

#define rep(_, n) int _; for(_ = 0; _ < n; _++)

#define in(_) cin >> _;
#define in2(_0, _1) cin >> _0 >> _1;
#define in3(_0, _1, _2) cin >> _0 >> _1 >> _2;
#define vin(a) { rep (_, sz (a)) { in (a[_]) }}
#define vvin(r, c) { rep(__,r) { rep(_,c) { in (matrix[__][_]) } } }
#define br cout << "\n";
#define out(_, __) cout << _ << __;
#define o(_) out(_, " ")
#define vout(__) for (auto _ : __) { o (_) } br
#define vvout(___)  for (auto __ : ___) { vout (__); }

#define oyes out("YES","\n")
#define ono out("NO", "\n")
/*
Unweighted Graph
*/
struct Graph {
    vector<vector<int >> adj;
    int n;
    vector<bool> visited;
    vector<int> roots;
    ll dp[int(2e5 + 1)][2];
    ll arr[int(2e5 + 1)][2];

    // vector<int> root_of;
    // vector<int> parent_of;
    // map<int, int> cluster_size;
    // vector<int> height;
    // vector<int> eulerian;
    // vector<int> first;
    // vector<int> segtree;
    // vector<int> subtree_size;
    // int timer;
    // vector<int> tin, tout;
    // int depth;

    Graph(int no_of_nodes, int no_of_edges, bool fill = true) {
        adj.resize(no_of_nodes);
        n = no_of_nodes;
        visited.assign(no_of_nodes, false);

        for (int i = 0; i < no_of_nodes; i++) {
            dp[i][0] = 0;
            dp[i][1] = 0;
        }

        // height.resize (no_of_nodes);
        // first.resize (no_of_nodes);
        // timer = 0;
        // tin.resize (no_of_nodes);
        // tout.resize (no_of_nodes);
        // subtree_size.resize (no_of_nodes);
        // depth = -1;

        if (fill) {
            if (no_of_edges == -1) {
                input();
            } else {
                input(no_of_edges);
            }

            DFS();
            // int m = eulerian.size();
            // segtree.resize (m * 4);
            // build (1, 0, m - 1);
        }
    }

    void clear() {
        visited.clear();
        // height.clear();
        // first.clear();
        // eulerian.clear();
        // tin.clear();
        // tout.clear();
        // subtree_size.clear();
        // timer = 0;
        // depth = -1;
        // segtree.clear();
    }

    void input(int no_of_edges) {
        for (int i = 0; i < no_of_edges; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    void input() {
        for (int i = 0; i < n; i++) {
            int u;
            cin >> u;
            u--;

            if (u == -2) {
                roots.push_back(i);
            } else {
                adj[u].push_back(i);
                adj[i].push_back(u);
            }
        }
    }

    void DFS() {
        visited.assign(n, false);

        if (roots.empty()) {
            roots.push_back(0);
        }

        for (int root : roots) {
            dfs(root, 0, -1, root, true);
        }
    }

    void dfs(int node, int level = 0, int parent = -1, int root = 0, bool modify = false);

    void bfs(int root, int level = 0) {
        queue<int> q;
        q.push(root);
        visited[root] = true;

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();

            for (int u : adj[vertex]) {
                if (!visited[u]) {
                    visited[u] = true;
                    q.push(u);
                }
            }
        }
    }

    /*
    void clusters() {
        visited.assign(n, false);
        roots.clear();

        for (int vertex = 0; vertex < n; ++vertex) {
            if (!visited[vertex]) {
                roots.push_back(vertex);
                dfs(vertex, 0, -1, vertex, false);
            }
        }
    }

    bool is_ancestor (int parents, int child) {
        return tin[parents] <= tin[child] && tout[parents] >= tout[child];
    }

    void build (int node, int begin, int end) {
        if (begin == end) {
            segtree[node] = eulerian[begin];
        } else {
            int mid = (begin + end) / 2;
            build (node << 1, begin, mid);
            build (node << 1 | 1, mid + 1, end);
            int l = segtree[node << 1], r = segtree[node << 1 | 1];
            segtree[node] = (height[l] < height[r]) ? l : r;
        }
    }
    int query (int node, int begin, int end, int L, int R) {
        if (begin > R || end < L) {
            return -1;
        }

        if (begin >= L && end <= R) {
            return segtree[node];
        }

        int mid = (begin + end) >> 1;
        int left = query (node << 1, begin, mid, L, R);
        int right = query (node << 1 | 1, mid + 1, end, L, R);

        if (left == -1) {
            return right;
        }

        if (right == -1) {
            return left;
        }

        return height[left] < height[right] ? left : right;
    }
    int lca (int u, int v) {
        int left = first[u], right = first[v];

        if (left > right) {
            swap (left, right);
        }

        return query (1, 0, eulerian.size() - 1, left, right);
    }
    */
};

void Graph::dfs(int node, int level, int parent, int root, bool modify) {
    visited[node] = true;

    if (modify) {
        // root_of[node] = root;
        // parent_of[node] = parent;
        // cluster_size[root]++;
        // tin[node] = ++timer;
        // height[node] = level;
        // first[node] = eulerian.size();
        // eulerian.push_back (node);
        // depth = max (depth, level);
    }

    for (int to : adj[node]) {
        if (!visited[to]) {
            dfs(to, level + 1, node, root, modify);
            ll one = abs(arr[node][0] - arr[to][0]);
            ll two = abs(arr[node][0] - arr[to][1]);
            ll three = abs(arr[node][1] - arr[to][0]);
            ll four = abs(arr[node][1] - arr[to][1]);
            dp[node][0] += max(dp[to][0] + one, dp[to][1] + two);
            dp[node][1] += max(dp[to][0] + three, dp[to][1] + four);
            // dp [node][0] += max(dp[to][0] + abs(a[node][0] - a[to][0]), dp[to][1] + abs(a[node][0] - a[to][1]));
            // dp [node][1] += max(dp[to][0] + abs(a[node][1] - a[to][0]), dp[to][1] + abs(a[node][1] - a[to][1]));

            if (modify) {
                // eulerian.push_back (node);
                // subtree_size[node] += subtree_size[to];
            }
        }
    }

    if (modify) {
        // subtree_size[node]++;
        // tout[node] = ++timer;
    }
}

int solve() {
    fastio
    int n;
    in (n)
    Graph g (n, -1, false);

    for (int i = 0; i < n; i++) {
        cin >> g.arr[i][0];
        cin >> g.arr[i][1];
    }

    g.input(n - 1);
    g.DFS();
    out(max(g.dp[0][0], g.dp[0][1]), "\n");
    return 0;
}

int main() {
    fastio;
    int t = 1;
    in (t);

    while (t--) {
        solve();
    }
}
