#include "bits/stdc++.h"
using namespace std;

struct Weighted_Graph {
    struct Weight;
    struct Node;
    struct Edge;
    struct Component;

    struct Weight {
        int weight;

        Weight()
            : weight(0) {}

        Weight(int weight)
            : weight(weight) {}
    };

    struct Edge {
        Node *neighbor;
        Weight weight;

        Edge(Node *neighbor, Weight weight)
            : neighbor(neighbor), weight(weight) {}
    };

    struct Node {
        int id;
        vector<Edge> neighbors;
        bool visited = false;

        Component *component = nullptr;

        Node(int id)
            : id(id) {}
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

    Weighted_Graph(int no_of_nodes, int no_of_edges, vector<pair<int, int, int>> edges) {
        this->no_of_nodes = no_of_nodes;
        this->no_of_edges = no_of_edges;
        for (int i = 0; i < no_of_nodes; i++) {
            nodes.push_back(new Node(i));
        }

        for (int i = 0; i < no_of_edges; i++) {
            int u = edges[i].first;
            int v = edges[i].second;
            int w = edges[i].third;
            nodes[u]->neighbors.push_back(Edge(nodes[v], Weight(w)));
            nodes[v]->neighbors.push_back(Edge(nodes[u], Weight(w)));
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
