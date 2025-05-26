#include "bits/stdc++.h"
using namespace std;

struct Tree {
    struct Node;

    struct Node {
        int id;
        Node *parent = nullptr;
        vector<Node *> children;
        bool visited = false;

        Node(int id)
            : id(id) {}

        Node(int id, Node *parent)
            : id(id), parent(parent) {}
    };

    int no_of_nodes;
    vector<Node *> nodes;

    Tree(int no_of_nodes, vector<int> parents) {
        this->no_of_nodes = no_of_nodes;

        for (int i = 0; i < no_of_nodes; i++) {
            nodes.push_back(new Node(i));
        }

        for (int i = 0; i < no_of_nodes; i++) {
            int parent_id = parents[i];

            if (parent_id == -1) {
                nodes[i]->parent = nullptr;
            } else {
                Node *parent = nodes[parent_id];
                nodes[i]->parent = parent;
                parent->children.push_back(nodes[i]);
            }
        }
    }

    void dfs(Node *node) {
        node->visited = true;

        for (Node *child : node->children) {
            if (!child->visited) {
                dfs(child);
            }
        }
    }

    void solution();
};
