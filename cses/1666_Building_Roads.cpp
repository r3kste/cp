#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

struct Graph {
    struct Node {
        int id;
        vector<Node*> neighbors;

        int component_id = -1;

        Node(int id) : id(id) {}

        Node(int id, vector<Node*> neighbors) : id(id), neighbors(neighbors) {}
    };

    int no_of_nodes;
    int no_of_edges;
    vector<Node*> nodes;

    vector<Node*> roots;
    vector<bool> visited;

    int no_of_components = 0;

    Graph(int no_of_nodes, int no_of_edges, vector<pair<int, int >> edges) {
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

        this->visited.assign(no_of_nodes, false);
    }

    void dfs_reset() {
        visited.assign(no_of_nodes, false);
    }

    void dfs(Node* node, int component_id) {
        visited[node->id] = true;
        node->component_id = component_id;
        for (Node* neighbor : node->neighbors) {
            if (!visited[neighbor->id]) {
                dfs(neighbor, component_id);
            }
        }
    }

    int connected_components() {
        no_of_components = 0;
        for (int i = 0; i < no_of_nodes; i++) {
            if (!visited[i]) {
                roots.push_back(nodes[i]);
                no_of_components++;
                dfs(nodes[i], no_of_components);
            }
        }

        return no_of_components;
    }

    void solution();
};

void Graph::solution() {
    connected_components();
    cout << no_of_components - 1 << endl;
    for (int i = 0; i < no_of_components - 1; i++) {
        cout << roots[i]->id + 1 << " " << roots[i + 1]->id + 1 << endl;
    }
}


void test() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int >> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--;
        edges[i].second--;
    }

    Graph graph(n, m, edges);
    graph.solution();
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