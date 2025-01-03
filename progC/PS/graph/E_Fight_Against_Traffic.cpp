#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

struct Node {
    int id;
    vector<int> children = vector<int>();

    int distance_from_s = 0;
    int distance_from_t = 0;

public:
    Node(int id) : id(id) {}

    Node() {
        this->id = -1;
        this->children = vector<int>();
        this->distance_from_s = LLONG_MAX;
        this->distance_from_t = LLONG_MAX;
    }
};

class Graph {
    int n;
    int no_of_edges;
    int source;
    int target;
    vector<Node> nodes;
    vector<int> visited;

public:
    Graph(int n, int no_of_edges, int s, int t) {
        this->n = n;
        this->no_of_edges = no_of_edges;
        this->source = s - 1;
        this->target = t - 1;
        this->nodes = vector<Node>(n);

        for (int i = 0; i < n; i++) {
            this->nodes[i] = Node(i);
        }

        for (int i = 0; i < no_of_edges; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            this->nodes[u].children.push_back(v);
            this->nodes[v].children.push_back(u);
        }
    }

    void answer() {
        visited = vector<int>(n, -1);
        this->bfs(this->source);

        for (int i = 0; i < n; i++) {
            nodes[i].distance_from_s = visited[i];
        }

        visited = vector<int>(n, -1);
        this->bfs(this->target);

        for (int i = 0; i < n; i++) {
            nodes[i].distance_from_t = visited[i];
        }

        int current_min = nodes[target].distance_from_s;
        int res = 0;

        for (int node1_idx = 0; node1_idx < n; node1_idx++) {
            for (int node2_idx = node1_idx + 1; node2_idx < n; node2_idx++) {
                if (nodes[node1_idx].distance_from_s == LLONG_MAX || nodes[node2_idx].distance_from_t == LLONG_MAX) {
                    continue;
                }

                if (find(nodes[node1_idx].children.begin(), nodes[node1_idx].children.end(), node2_idx) != nodes[node1_idx].children.end()) {
                    continue;
                }

                int new_distance = nodes[node1_idx].distance_from_s + nodes[node2_idx].distance_from_t + 1;

                if (new_distance < current_min) {
                    continue;
                }

                int new_distance2 = nodes[node2_idx].distance_from_s + nodes[node1_idx].distance_from_t + 1;

                if (new_distance2 < current_min) {
                    continue;
                }

                res++;
            }
        }

        cout << res << endl;
    }

private:
    void dfs(int node) {
        for (int child : this->nodes[node].children) {
            this->dfs(child);
        }
    }

    void bfs(int node) {
        queue<pair<int, int >> q;
        q.push({node, 0});
        visited[node] = 0;
        while (!q.empty()) {
            auto [node, depth] = q.front();
            q.pop();
            for (int child : this->nodes[node].children) {
                if (visited[child] != -1) {
                    continue;
                }

                visited[child] = depth + 1;
                q.push({child, depth + 1});
            }
        }
    }
};

int32_t main() {
    fastio;
    int n, no_of_edges, s, t;
    cin >> n >> no_of_edges >> s >> t;
    Graph tree(n, no_of_edges, s, t);
    tree.answer();
}
