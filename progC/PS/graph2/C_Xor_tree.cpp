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
    struct Node;
    struct Component;

    struct Node {
        int id;
        vector<Node *> neighbors;
        bool visited = false;

        Component *component = nullptr;
        int state;
        int goal;

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
    vector<int> res;

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
        for (Node *neighbor : node->neighbors) {
            if (!neighbor->visited) {
                dfs(neighbor);
            }
        }
    }

    void dfs(Node *node, Component *component) {
        node->visited = true;
        component->nodes.push_back(node);
        node->component = component;
        for (Node *neighbor : node->neighbors) {
            if (!neighbor->visited) {
                dfs(neighbor, component);
            }
        }
    }

    void dfs(Node *node, int height, int even_toggles, int odd_toggles) {
        node->visited = true;
        if (height % 2 == 0) {
            node->state ^= even_toggles % 2;
        }

        else {
            node->state ^= odd_toggles % 2;
        }
        if (node->goal != node->state) {
            res.push_back(node->id + 1);
            if (height % 2 == 0) {
                even_toggles++;
            }

            else {
                odd_toggles++;
            }
        }

        for (Node *neighbor : node->neighbors) {
            if (!neighbor->visited) {
                dfs(neighbor, height + 1, even_toggles, odd_toggles);
            }
        }
    }

    int connected_components() {
        for (Node *node : nodes) {
            node->visited = false;
        }

        int no_of_components = 0;
        for (Node *node : nodes) {
            if (!node->visited) {
                Component *component = new Component(++no_of_components);
                components.push_back(component);
                dfs(node, component);
            }
        }

        return no_of_components;
    }

    void solution();
};

void test() {
    int n;
    cin >> n;
    int m = n - 1;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--;
        edges[i].second--;
    }

    vector<int> init(n);
    vector<int> goal(n);

    for (int i = 0; i < n; i++) {
        cin >> init[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> goal[i];
    }
    Graph graph(n, m, edges);

    for (int i = 0; i < n; i++) {
        Graph::Node *node = graph.nodes[i];
        node->state = init[i];
        node->goal = goal[i];
    }
    graph.dfs(graph.nodes[0], 0, 0, 0);
    cout << graph.res.size() << endl;

    for (int i : graph.res) {
        cout << i << endl;
    }
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