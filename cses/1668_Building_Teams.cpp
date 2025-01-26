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

        int team_id = -1;

        Node* parent = nullptr;

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

    void bfs(Node* node) {
        struct State {
            Node* node;
        };
        queue<State> q;
        q.push({node});

        while (!q.empty()) {
            State state = q.front();
            q.pop();
            Node* node = state.node;
            node->visited = true;

            if (node->id == no_of_nodes - 1) {
                break;
            }

            for (Node* neighbor : node->neighbors) {
                if (!neighbor->visited) {
                    neighbor->parent = node;
                    q.push({neighbor});
                }
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

    void solution() {
        connected_components();

        queue<Node*> current;
        for (Component* component : components) {
            Node* root = component->nodes[0];
            current.push(root);
            root->team_id = 0;
        }

        while (!current.empty()) {
            Node* node = current.front();
            current.pop();

            for (Node* neighbor : node->neighbors) {
                if (neighbor->team_id == -1) {
                    neighbor->team_id = 1 - node->team_id;
                    current.push(neighbor);
                } else if (neighbor->team_id == node->team_id) {
                    cout << "IMPOSSIBLE" << endl;
                    return;
                }
            }
        }

        for (Node* node : nodes) {
            cout << node->team_id + 1 << " ";
        }
    }
};


void test() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int >> edges(m);
    for (int i = 0; i< m; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = make_pair(u - 1, v - 1);
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