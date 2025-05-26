#include "bits/stdc++.h"
using namespace std;

struct Graph {
    struct Node;
    struct Component;

    int n;
    int m;
    vector<Node *> nodes;
    vector<Component *> components;

    struct Node {
        int id;
        vector<Node *> neighbors;
        bool visited = false;

        Node *parent = nullptr;

        Component *component = nullptr;

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

    Graph(int n, int m, const vector<pair<int, int>> &edges) {
        this->n = n;
        this->m = m;
        for (int i = 0; i < n; i++) {
            nodes.push_back(new Node(i));
        }

        for (int i = 0; i < m; i++) {
            int u = edges[i].first;
            int v = edges[i].second;
            nodes[u]->neighbors.push_back(nodes[v]);
            nodes[v]->neighbors.push_back(nodes[u]);
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

    void _bfs(Node *node) {
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

    void solution();
};
