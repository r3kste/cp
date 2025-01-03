#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

struct Node
{
    int id;
    int parent;
    vector<int> children = vector<int>();

    int distance_from_s = 0;
    int distance_from_t = 0;

public:
    Node(int id, int parent) : id(id), parent(parent) {}

    Node()
    {
        this->id = -1;
        this->children = vector<int>();
        this->distance_from_s = 0;
        this->distance_from_t = 0;
    }
};

class Graph
{
    int n;
    int source;
    int target;
    vector<Node> nodes;
    vector<int> visited;

public:
    Graph(int n, int m, int s, int t)
    {
        this->n = n;
        this->source = s - 1;
        this->target = t - 1;

        this->nodes = vector<Node>(n);
        this->nodes[0] = Node(0, -1);

        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            this->nodes[u] = Node(u, v);
            this->nodes[v] = Node(v, u);
        }

        for (int i = 0; i < n; i++)
        {
            if (nodes[i].parent == -1)
            {
                continue;
            }
            this->nodes[nodes[i].parent].children.push_back(i);
        }
    }

    void answer()
    {
        visited = vector<int>(n, -1);
        this->bfs(this->source);
        for (int i = 0; i < n; i++)
        {
            nodes[i].distance_from_s = visited[i];
        }

        visited = vector<int>(n, -1);
        this->bfs(this->target);
        for (int i = 0; i < n; i++)
        {
            nodes[i].distance_from_t = visited[i];
        }

        int current_min = nodes[target].distance_from_s;

        int res = 0;
        for (int node1_idx = 0; node1_idx < n; node1_idx++)
        {
            for (int node2_idx = node1_idx + 1; node2_idx < n; node2_idx++)
            {
                int new_distance = nodes[node1_idx].distance_from_s + nodes[node2_idx].distance_from_t + 1;
                if (new_distance >= current_min)
                {
                    res++;
                }
            }
        }

        cout << res << endl;
    }

private:
    void dfs(int node)
    {
        for (int child : this->nodes[node].children)
        {
            this->dfs(child);
        }
    }

    void bfs(int node)
    {
        queue<pair<int, int>> q;
        q.push({node, 0});
        visited[node] = 0;

        while (!q.empty())
        {
            auto [node, depth] = q.front();
            q.pop();
            for (int child : this->nodes[node].children)
            {
                if (visited[child] != -1)
                {
                    continue;
                }
                visited[child] = depth + 1;
                q.push({child, depth + 1});
            }
        }
    }
};

int32_t main()
{
    fastio;
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    Graph tree(n, m, s, t);
    tree.answer();
}
