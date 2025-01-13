#include "bits/stdc++.h"
using namespace std;

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

    void solution();
};
