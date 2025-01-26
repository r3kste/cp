#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

struct Tree {
    struct Node;

    struct Node {
        int id;
        Node* parent = nullptr;
        vector<Node*> children;
        bool visited = false;

        bool respects = false;
        bool can_be_removed = true;

        Node(int id) : id(id) {}

        Node(int id, Node* parent) : id(id), parent(parent) {}
    };

    int no_of_nodes;
    vector<Node*> nodes;

    Tree(int no_of_nodes, vector<int> parents, vector<bool> respects) {
        this->no_of_nodes = no_of_nodes;

        for (int i = 0; i < no_of_nodes; i++) {
            Node* node = new Node(i);
            node->respects = respects[i];
            nodes.push_back(node);
        }

        for (int i = 0; i < no_of_nodes; i++) {
            int parent_id = parents[i];

            if (parent_id == -1) {
                nodes[i]->parent = nullptr;
            } else {
                Node* parent = nodes[parent_id];
                nodes[i]->parent = parent;
                parent->children.push_back(nodes[i]);
            }
        }
    }

    void dfs(Node* node) {
        node->visited = true;

        for (Node* child : node->children) {
            if (!child->visited) {
                dfs(child);
            }
        }
    }

    void solution() {
        for (Node* node : nodes) {
            if (node->respects) {
                node->can_be_removed = false;
                Node* parent = node->parent;

                if (parent != nullptr) {
                    parent->can_be_removed = false;
                }
            }
        }

        vector<int> res;

        for (Node* node : nodes) {
            if (node->can_be_removed) {
                res.push_back(node->id + 1);
            }
        }

        if (res.size() == 0) {
            cout << -1 << endl;
        } else {
            for (int i : res) {
                cout << i << " ";
            }

            cout << endl;
        }
    }
};

void test() {
    int n;
    cin >> n;
    vector<int> parents(n);
    vector<bool> respects(n, false);

    for (int i = 0; i < n; i++) {
        int parent, respect;
        cin >> parent >> respect;
        respects[i] = bool(respect ^ 1);

        if (parent != -1) {
            parent--;
        }

        parents[i] = parent;
    }

    Tree tree(n, parents, respects);
    tree.solution();
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
