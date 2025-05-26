#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

struct BinaryTree {
    struct Node {
        int id;
        Node *left;
        Node *right;

        Node(int id, Node *left, Node *right)
            : id(id), left(left), right(right) {}
    };

    int no_of_nodes;
    Node *root;
    vector<Node *> nodes;

    BinaryTree(int n, int root, vector<pair<int, int>> children) {
        no_of_nodes = n;
        for (int i = 0; i < n; i++) {
            nodes.push_back(new Node{i + 1, nullptr, nullptr});
        }

        this->root = nodes[root - 1];
        for (int i = 0; i < n; i++) {
            if (children[i].first != 0)
                nodes[i]->left = nodes[children[i].first - 1];
            if (children[i].second != 0)
                nodes[i]->right = nodes[children[i].second - 1];
        }
    }

    void answer() {
        cout << f(root) << endl;
    }

    int f(Node *node) {
        if (node == nullptr)
            return 0;
        if (node->left == nullptr && node->right == nullptr)
            return 0;
        int left = MOD;
        int right = MOD;
        if (node->left != nullptr) {
            left = f(node->left);
        }

        if (node->right != nullptr) {
            right = f(node->right);
        }

        return min(left, right);
    }
};

void test() {
    int n;
    cin >> n;
    vector<pair<int, int>> children;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        children.push_back({l, r});
    }

    BinaryTree tree(n, 1, children);
    tree.answer();
}

int32_t main() {
    fastio;
    int t;
    cin >> t;

    while (t--) {
        test();
    }

    return 0;
}