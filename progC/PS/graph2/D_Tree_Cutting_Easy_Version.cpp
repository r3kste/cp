#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

enum Color {
    RED,
    BLUE,
    NONE,
};

struct Graph {
    struct Node;
    struct Component;

    struct Node {
        int id;
        vector<Node *> neighbors;
        bool visited = false;

        Component *component = nullptr;
        Color color = NONE;
        int subtree_red = 0;
        int subtree_blue = 0;

        Node(int id)
            : id(id) {}

        Node(int id, vector<Node *> neighbors)
            : id(id), neighbors(neighbors) {}
    };

    struct Component {
        int id;
        vector<Node *> nodes;

        Component(int id)
            : id(id) {}

        Component(int id, vector<Node *> nodes)
            : id(id), nodes(nodes) {}
    };

    int no_of_nodes;
    int no_of_edges;
    vector<Node *> nodes;
    vector<Component *> components;

    Graph(int no_of_nodes, int no_of_edges, vector<pair<int, int>> edges) {
        this->no_of_nodes = no_of_nodes;
        this->no_of_edges = no_of_edges;
        for (int i = 0; i < no_of_nodes; i++) {
            nodes.push_back(new Node(i));
        }

        for (int i = 0; i < no_of_edges; i++) {
            int u = edges[i].first;
            int v = edges[i].second;
            nodes[u]->neighbors.push_back(nodes[v]);
            nodes[v]->neighbors.push_back(nodes[u]);
        }
    }

    void dfs(Node *node) {
        node->visited = true;
        int red = (node->color == RED);
        int blue = (node->color == BLUE);
        for (Node *neighbor : node->neighbors) {
            if (!neighbor->visited) {
                dfs(neighbor);
                red += neighbor->subtree_red;
                blue += neighbor->subtree_blue;
            }
        }

        node->subtree_red = red;
        node->subtree_blue = blue;
    }

    void solution();
};

void test() {
    int n;
    cin >> n;
    vector<int> a(n);
    int total_red = 0;
    int total_blue = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int m = n - 1;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--;
        edges[i].second--;
    }

    Graph graph(n, m, edges);

    for (int i = 0; i < n; i++) {
        int c = a[i];

        if (c == 1) {
            graph.nodes[i]->color = RED;
            total_red++;
        } else if (c == 2) {
            graph.nodes[i]->color = BLUE;
            total_blue++;
        }
    }
    graph.dfs(graph.nodes[0]);
    int res = 0;

    for (Graph::Node *node : graph.nodes) {
        if (node->subtree_red == total_red && node->subtree_blue == 0) {
            res++;
        }

        if (node->subtree_blue == total_blue && node->subtree_red == 0) {
            res++;
        }
    }
    cout << res << endl;
}

int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;

    while (t--) {
        test();
    }

    return 0;
}