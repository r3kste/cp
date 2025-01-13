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
        vector<Node*> neighbors;
        bool visited = false;

        Component* component = nullptr;

        Node(int id) : id(id) {}

        Node(int id, vector<Node*> neighbors) : id(id), neighbors(neighbors) {}
    };

    struct Component {
        int id;
        vector<Node*> nodes;

        Component(int id) : id(id) {}

        Component(int id, vector<Node*> nodes) : id(id), nodes(nodes) {}
    };

    int no_of_nodes;
    int no_of_edges;
    vector<Node*> nodes;
    vector<Component*> components;

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
    }

    void dfs(Node* node) {
        node->visited = true;
        for (Node* neighbor : node->neighbors) {
            if (!neighbor->visited) {
                dfs(neighbor);
            }
        }
    }

    void dfs(Node* node, Component* component) {
        node->visited = true;
        component->nodes.push_back(node);
        node->component = component;
        for (Node* neighbor : node->neighbors) {
            if (!neighbor->visited) {
                dfs(neighbor, component);
            }
        }
    }

    int connected_components() {
        for (Node* node : nodes) {
            node->visited = false;
        }

        int no_of_components = 0;
        for (Node* node : nodes) {
            if (!node->visited) {
                Component* component = new Component(++no_of_components);
                components.push_back(component);
                dfs(node, component);
            }
        }

        return no_of_components;
    }

    int connected_components(vector<int>& roots) {
        for (Node* node : nodes) {
            node->visited = false;
        }

        int no_of_components = 0;

        for (int root : roots) {
            if (!nodes[root]->visited) {
                Component* component = new Component(++no_of_components);
                components.push_back(component);
                dfs(nodes[root], component);
            }
        }

        return no_of_components;
    }

    void solution();
};

void test() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> roots(k);

    for (int i = 0; i < k; i++) {
        cin >> roots[i];
        roots[i]--;
    }

    vector<pair<int, int >> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--;
        edges[i].second--;
    }

    Graph graph(n, m, edges);
    graph.connected_components(roots);
    int neutral = 0;

    for (Graph::Node* node : graph.nodes) {
        if (node->component == nullptr) {
            neutral++;
        }
    }
    Graph::Component* biggest_governmet = graph.components[0];
    int result = 0;

    for (Graph::Component* component : graph.components) {
        int size = component->nodes.size();
        result += size * (size - 1) / 2;

        if (size > biggest_governmet->nodes.size()) {
            biggest_governmet = component;
        }
    }
    int biggest_governmet_size = biggest_governmet->nodes.size();
    result -= biggest_governmet_size * (biggest_governmet_size - 1) / 2;
    biggest_governmet_size += neutral;
    result += biggest_governmet_size * (biggest_governmet_size - 1) / 2;
    cout << result - m << endl;
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