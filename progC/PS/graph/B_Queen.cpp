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
    bool respects;
    vector<int> children;

public:
    Node(int id, int parent, bool respects) : id(id), parent(parent), respects(respects) {}
};

class Graph
{
    int n;
    vector<Node> nodes;

public:
    Graph(int n, const vector<int> &parents, const vector<bool> &respects)
    {
        this->n = n;

        for (int i = 0; i < n; i++)
        {
            int parent = parents[i] - 1;
            if (parent == -2)
            {
                parent = -1;
            }
            this->nodes.push_back(Node(i, parent, respects[i]));
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

    bool can_be_removed(int node)
    {
        if (this->nodes[node].respects)
        {
            return false;
        }

        for (int child : this->nodes[node].children)
        {
            if (this->nodes[child].respects)
            {
                return false;
            }
        }
        return true;
    }

    void answer()
    {
        this->dfs(0);
        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            if (this->can_be_removed(i))
            {
                ans.push_back(i);
            }
        }
        if (ans.size() == 0)
        {
            cout << -1 << endl;
            return;
        }

        sort(ans.begin(), ans.end());
        for (int i : ans)
        {
            cout << i + 1 << " ";
        }
        cout << endl;
    }

private:
    void dfs(int node)
    {
        for (int child : this->nodes[node].children)
        {
            this->dfs(child);
        }
    }
};

int32_t main()
{
    fastio;
    int n;
    cin >> n;
    vector<int> parents(n);
    vector<bool> respects(n);
    for (int i = 0; i < n; i++)
    {
        cin >> parents[i];
        int respect;
        cin >> respect;
        respects[i] = respect == 0;
    }
    Graph tree(n, parents, respects);
    tree.answer();
}