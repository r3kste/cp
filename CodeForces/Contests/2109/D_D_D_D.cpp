#include "bits/stdc++.h"
using namespace std;

#define integer int
#define int long long
#define endl '\n'

#define MOD (int)(2e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

struct Graph
{
    struct Node;
    struct Component;

    struct Node
    {
        int id;
        vector<Node *> neighbors;
        bool visited = false;

        Node *parent = nullptr;

        Component *component = nullptr;

        Node(int id) : id(id) {}

        Node(int id, vector<Node *> neighbors) : id(id), neighbors(neighbors) {}
    };

    struct Component
    {
        int id;
        vector<Node *> nodes;

        Component(int id) : id(id) {}

        Component(int id, vector<Node *> nodes) : id(id), nodes(nodes) {}
    };

    int no_of_nodes;
    int no_of_edges;
    vector<Node *> nodes;
    vector<Component *> components;

    vector<vector<int>> dist;

    Graph(int no_of_nodes, int no_of_edges, vector<pair<int, int>> &edges)
    {
        this->no_of_nodes = no_of_nodes;
        this->no_of_edges = no_of_edges;
        for (int i = 0; i < no_of_nodes; i++)
        {
            nodes.push_back(new Node(i));
        }

        for (int i = 0; i < no_of_edges; i++)
        {
            int u = edges[i].first;
            int v = edges[i].second;
            nodes[u]->neighbors.push_back(nodes[v]);
            nodes[v]->neighbors.push_back(nodes[u]);
        }

        dist = vector<vector<int>>(no_of_nodes, vector<int>(2, MOD));
    }

    void dfs(Node *node)
    {
        node->visited = true;
        for (Node *neighbor : node->neighbors)
        {
            if (!neighbor->visited)
            {
                dfs(neighbor);
            }
        }
    }

    void bfs(Node *node)
    {
        for (Node *node : nodes)
        {
            node->visited = false;
        }
        dist.assign(no_of_nodes, vector<int>(2, MOD));

        struct State
        {
            Node *node;
            int parity;
        };
        queue<State> q;
        q.push({node, 0});
        dist[node->id][0] = 0;

        while (!q.empty())
        {
            State state = q.front();
            q.pop();
            Node *node = state.node;
            int parity = state.parity;

            for (Node *neighbor : node->neighbors)
            {
                if (dist[neighbor->id][!parity] > dist[node->id][parity] + 1)
                {
                    neighbor->parent = node;
                    dist[neighbor->id][!parity] = dist[node->id][parity] + 1;
                    q.push({neighbor, !parity});
                }
            }
        }
    }

    void dfs(Node *node, Component *component)
    {
        node->visited = true;
        component->nodes.push_back(node);
        node->component = component;

        for (Node *neighbor : node->neighbors)
        {
            if (!neighbor->visited)
            {
                dfs(neighbor, component);
            }
        }
    }

    int connected_components()
    {
        for (Node *node : nodes)
        {
            node->visited = false;
        }

        int no_of_components = 0;

        for (Node *node : nodes)
        {
            if (!node->visited)
            {
                Component *component = new Component(++no_of_components);
                components.push_back(component);
                dfs(node, component);
            }
        }

        return no_of_components;
    }

    bool is_cyclic(Node *node)
    {
        for (Node *node : nodes)
        {
            node->visited = false;
        }

        struct State
        {
            Node *node;
            Node *parent;
            int cycle_length;
        };

        queue<State> q;
        q.push({node, nullptr, 0});
    }
    void solution(int S, int min_odd);
};

void Graph::solution(int S, int min_odd)
{
    for (int i = 0; i < no_of_nodes; i++)
    {
        bool possible = false;
        possible |= (dist[i][S % 2] <= S);
        if (min_odd != MOD)
        {
            possible |= (dist[i][1 - S % 2] <= S - min_odd);
        }
        cout << (possible ? 1 : 0);
    }
    cout << "\n";
}

void test()
{
    int n, m, l;
    cin >> n >> m >> l;
    vector<pair<int, int>> edges;
    multiset<int> A;
    int S = 0;
    int min_odd = MOD;
    for (int i = 0; i < l; i++)
    {
        int t;
        cin >> t;
        S += t;
        if (t % 2)
        {
            if (t < min_odd)
            {
                min_odd = t;
            }
        }
        A.insert(t);
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        edges.push_back({u, v});
    }

    Graph g(n, m, edges);
    g.bfs(g.nodes[0]);
    g.solution(S, min_odd);
}

int32_t main()
{
    fastio;
    int t = 1;
    cin >> t;

    while (t--)
    {
        test();
    }

    return 0;
}