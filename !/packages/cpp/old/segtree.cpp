#include<bits/stdc++.h>

using namespace std;

template<typename T>
struct segtree {
    struct range {
        int L;
        int R;

        [[nodiscard]] int mid() const {
            return L + (R - L) / 2;
        }
    };

    static const T DEFAULT_VAL = 0;
    static const T DEFAULT_LAZY = 0;
    struct node {
        T val;
        T lazy;

        node() {
            val = DEFAULT_VAL;
            lazy = DEFAULT_LAZY;
        }
    };

    int n;
    vector<int> arr;
    vector<node> tree;

    explicit segtree(vector<int>& array) {
        arr = array;
        n = (int) array.size();
        tree.resize(4 * n + 1);
        build();
    }

    T default_val() {
        /**/
        return 0;
        /**/
    }

    T build_operation(int left_vertex, int right_vertex);
    T update_operation(int vertex, T value);
    T query_operation(T left_subtree, T right_subtree);
    T lazy_operation(T value, int vertex, range borders);

    void build(int vertex, range borders) {
        if (borders.L == borders.R) {
            if (borders.L <= n) {
                tree[vertex].val = arr[borders.L - 1];
            }
        } else {
            int mid = borders.mid();
            build(vertex << 1, {borders.L, mid});
            build(vertex << 1 | 1, {mid + 1, borders.R});
            tree[vertex].val = build_operation(vertex << 1, vertex << 1 | 1);
        }
    }

    void point_update(int target, T value, int vertex, range borders) {
        if (tree[vertex].lazy != DEFAULT_LAZY) {
            tree[vertex].val = lazy_operation(tree[vertex].lazy, vertex, borders);

            if (borders.L != borders.R) {
                tree[vertex << 1].lazy += tree[vertex].lazy;
                tree[vertex << 1 | 1].lazy += tree[vertex].lazy;
            }

            tree[vertex].lazy = DEFAULT_LAZY;
        }

        if (borders.L == borders.R) {
            tree[vertex].val = update_operation(vertex, value);
        } else {
            int mid = borders.mid();

            if (target <= mid) {
                point_update(target, value, vertex << 1, {borders.L, mid});
            } else {
                point_update(target, value, vertex << 1 | 1, {mid + 1, borders.R});
            }

            tree[vertex].val = build_operation(vertex << 1, vertex << 1 | 1);
        }
    }

    void range_update(range update_range, T value, int vertex, range borders) {
        if (tree[vertex].lazy != DEFAULT_LAZY) {
            tree[vertex].val = lazy_operation(tree[vertex].lazy, vertex, borders);

            if (borders.L != borders.R) {
                tree[vertex << 1].lazy += tree[vertex].lazy;
                tree[vertex << 1 | 1].lazy += tree[vertex].lazy;
            }

            tree[vertex].lazy = DEFAULT_LAZY;
        }

        if (borders.L > borders.R || borders.L > update_range.R || borders.R < update_range.L) {
            return;
        }

        if (borders.L >= update_range.L && borders.R <= update_range.R) {
            tree[vertex].val = lazy_operation(value, vertex, borders);

            if (borders.L != borders.R) {
                tree[vertex << 1].lazy += value;
                tree[vertex << 1 | 1].lazy += value;
            }

            return;
        }

        int mid = borders.mid();
        range_update(update_range, value, vertex << 1, {borders.L, mid});
        range_update(update_range, value, vertex << 1 | 1, {mid + 1, borders.R});
        tree[vertex].val = build_operation(vertex << 1, vertex << 1 | 1);
    }

    T point_query(int target, int vertex, range borders) {
        if (tree[vertex].lazy != DEFAULT_LAZY) {
            tree[vertex].val = lazy_operation(tree[vertex].lazy, vertex, borders);

            if (borders.L != borders.R) {
                tree[vertex << 1].lazy += tree[vertex].lazy;
                tree[vertex << 1 | 1].lazy += tree[vertex].lazy;
            }

            tree[vertex].lazy = DEFAULT_LAZY;
        }

        if (borders.L == borders.R) {
            return tree[vertex].val;
        } else {
            int mid = borders.mid();

            if (target <= mid) {
                return point_query(target, vertex << 1, {borders.L, mid});
            } else {
                return point_query(target, vertex << 1 | 1, {mid + 1, borders.R});
            }
        }
    }

    T range_query(range query_range, int vertex, range borders) {
        if (tree[vertex].lazy != DEFAULT_LAZY) {
            tree[vertex].val = lazy_operation(tree[vertex].lazy, vertex, borders);

            if (borders.L != borders.R) {
                tree[vertex << 1].lazy += tree[vertex].lazy;
                tree[vertex << 1 | 1].lazy += tree[vertex].lazy;
            }

            tree[vertex].lazy = DEFAULT_LAZY;
        }

        if (borders.L > query_range.R || borders.R < query_range.L) {
            return default_val();
        } else if (borders.L >= query_range.L && borders.R <= query_range.R) {
            return tree[vertex].val;
        } else {
            int mid = borders.mid();
            T left_subtree = range_query(query_range, vertex << 1, {borders.L, mid});
            T right_subtree = range_query(query_range, vertex << 1 | 1, {mid + 1, borders.R});
            return query_operation(left_subtree, right_subtree);
        }
    }

    void build() {
        build(1, {1, n});
    }

    void update(int target, T value) {
        point_update(target, value, 1, {1, n});
    }

    void update(range update_range, T value) {
        range_update(update_range, value, 1, {1, n});
    }

    T query(int target) {
        return point_query(target, 1, {1, n});
    }

    T query(range query_range) {
        return range_query(query_range, 1, {1, n});
    }
};

template<typename T>
T segtree<T>::build_operation(int left_vertex, int right_vertex) {
    /* How to combine two nodes into one parent node */
    return tree[left_vertex].val + tree[right_vertex].val;
    /**/
}

template<typename T>
T segtree<T>::update_operation(int vertex, T value) {
    /* How to update the value in tree[vertex] */
    return tree[vertex].val + value;
    /**/
}

template<typename T>
T segtree<T>::query_operation(T left_subtree, T right_subtree) {
    /* What should be returned as query's result after calculating for children */
    return left_subtree + right_subtree;
    /**/
}

template<typename T>
T segtree<T>::lazy_operation(T value, int vertex, range borders) {
    /* How to update the lazy of a vertex */
    return tree[vertex].val + (borders.R - borders.L + 1) * value;
    /**/
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);

    for (auto &i : arr) {
        cin >> i;
    }

    segtree<long long int> tree(arr);

    while (m--) {
        int operation;
        cin >> operation;

        if (operation == 1) {
            int l, r, value;
            cin >> l >> r >> value;
            tree.update({l, r}, value);
        } else {
            int k;
            cin >> k;
            cout << tree.query(k) << "\n";
        }
    }

    return 0;
}
