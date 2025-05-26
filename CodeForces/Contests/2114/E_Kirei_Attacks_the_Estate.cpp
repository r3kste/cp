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

        Node *parent = nullptr;

        Component *component = nullptr;

        int threat = 0;
        int max_threat = 0;
        int min_threat = 0;

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

    Graph(int no_of_nodes, int no_of_edges, const vector<pair<int, int>> &edges,
          vector<int> &threats) {
        this->no_of_nodes = no_of_nodes;
        this->no_of_edges = no_of_edges;
        for (int i = 0; i < no_of_nodes; i++) {
            nodes.push_back(new Node(i));
        }

        for (int i = 0; i < no_of_nodes; i++) {
            nodes[i]->threat = threats[i];
            nodes[i]->max_threat = threats[i];
            nodes[i]->min_threat = threats[i];
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
        if (node->parent != nullptr) {
            node->max_threat =
                max(node->max_threat, node->threat - node->parent->min_threat);
            node->min_threat =
                min(node->min_threat, node->threat - node->parent->max_threat);
        }
        for (Node *neighbor : node->neighbors) {
            if (!neighbor->visited) {
                neighbor->parent = node;
                dfs(neighbor);
            }
        }
    }

    void _dfs(Node *node) {
        node->visited = true;
        for (Node *neighbor : node->neighbors) {
            if (!neighbor->visited) {
                neighbor->parent = node;
                _dfs(neighbor);
            }
        }
    }

    void bfs(Node *node) {
        for (Node *node : nodes) {
            node->visited = false;
        }

        struct State {
            Node *node;
        };
        queue<State> q;
        q.push({node});

        while (!q.empty()) {
            State state = q.front();
            q.pop();
            Node *node = state.node;
            node->visited = true;

            if (node->id == no_of_nodes - 1) {
                break;
            }

            for (Node *neighbor : node->neighbors) {
                if (!neighbor->visited) {
                    neighbor->parent = node;
                    q.push({neighbor});
                }
            }
        }
    }

    void _dfs(Node *node, Component *component) {
        node->visited = true;
        component->nodes.push_back(node);
        node->component = component;

        for (Node *neighbor : node->neighbors) {
            if (!neighbor->visited) {
                neighbor->parent = node;
                _dfs(neighbor, component);
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
                _dfs(node, component);
            }
        }

        return no_of_components;
    }

    void solution() {
        dfs(nodes[0]);

        for (Node *node : nodes) {
            cout << node->max_threat << " ";
        }
        cout << endl;
    }
};

void test() {
    int n;
    cin >> n;
    vector<int> threats(n);

    for (int i = 0; i < n; i++) {
        cin >> threats[i];
    }

    vector<pair<int, int>> edges(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        edges[i] = {u, v};
    }

    Graph graph(n, n - 1, edges, threats);
    graph.solution();
}

int32_t main() {
    fastio;
    int t = 1;
    cin >> t;

    while (t--) {
        test();
    }

    return 0;
}
