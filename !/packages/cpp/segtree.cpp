#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct segtree {
    struct range {
        int _L;
        int _R;

        int L() const {
            return _L;
        }

        int R() const {
            return _R;
        }

        int M() const {
            return _L + (_R - _L) / 2;
        }
    }

    struct node {
        T val;

        node()
            : val(0) {}
    }

    int n;
    vector<int> arr;
    vector<node> tree;
    string op;
    T DEFAULT_VAL;

    segtree(vector<int> &array, string operation, T init_val) {
        arr = array;
        n = (int)array.size();
        int size = pow(2, ceil(log2(n)));
        tree.resize(2 * size);
        op = operation;
        DEFAULT_VAL = init_val;

        for (auto &node : tree) {
            node.val = init_val;
        }

        build();
    }

    void build() {
        build(1, {1, n});
    }

    void build(int vertex, range borders) {
        if (borders.L() == borders.R()) {
            if (borders.L() <= n) {
                tree[vertex].val = arr[borders.L() - 1];
            }
        } else {
            int mid = borders.M();
            int left_vertex = vertex << 1;
            int right_vertex = vertex << 1 | 1;
            build(left_vertex, {borders.L(), mid});
            build(right_vertex, {mid + 1, borders.R()});
            tree[vertex].val = build_operation(left_vertex, right_vertex);
        }
    }

    T build_operation(int left_vertex, int right_vertex) {
        switch (op) {
            case "sum":
                return tree[left_vertex].val + tree[right_vertex].val;

            case "max":
                return max(tree[left_vertex].val, tree[right_vertex].val);

            case "min":
                return min(tree[left_vertex].val, tree[right_vertex].val);

            case "gcd":
                return __gcd(tree[left_vertex].val, tree[right_vertex].val);

            case "lcm":
                return (tree[left_vertex].val * tree[right_vertex].val) / __gcd(tree[left_vertex].val, tree[right_vertex].val);

            case "xor":
                return tree[left_vertex].val ^ tree[right_vertex].val;

            default:
                return 0;
        }
    }

    void point_update(int target, T value) {
        point_update(target, value, 1, {1, n});
    }

    void point_update(int target, T value, int vertex, range borders) {
        if (borders.L() == borders.R()) {
            tree[vertex].val = value;
        } else {
            int mid = borders.M();
            int left_vertex = vertex << 1;
            int right_vertex = vertex << 1 | 1;

            if (target <= mid) {
                point_update(target, value, left_vertex, {borders.L(), mid});
            } else {
                point_update(target, value, right_vertex, {mid + 1, borders.R()});
            }

            tree[vertex].val = build_operation(left_vertex, right_vertex);
        }
    }

    void range_update(range update_range, T value) {
        range_update(update_range, value, 1, {1, n});
    }

    void range_update(range update_range, T value, int vertex, range borders) {
        if (borders.L() > update_range.R() || borders.R() < update_range.L()) {
            return;
        }

        if (borders.L() >= update_range.L() && borders.R() <= update_range.R()) {
            tree[vertex].val = value;
            return;
        }

        int mid = borders.M();
        int left_vertex = vertex << 1;
        int right_vertex = vertex << 1 | 1;
        range_update(update_range, value, left_vertex, {borders.L(), mid});
        range_update(update_range, value, right_vertex, {mid + 1, borders.R()});
        tree[vertex].val = build_operation(left_vertex, right_vertex);
    }

    T query_operation(T left_subtree, T right_subtree) {
        switch (op) {
            case "sum":
                return left_subtree + right_subtree;

            case "max":
                return max(left_subtree, right_subtree);

            case "min":
                return min(left_subtree, right_subtree);

            case "gcd":
                return __gcd(left_subtree, right_subtree);

            case "lcm":
                return (left_subtree * right_subtree) / __gcd(left_subtree, right_subtree);

            case "xor":
                return left_subtree ^ right_subtree;

            default:
                return 0;
        }
    }

    T query(int target) {
        return query(target, 1, {1, n});
    }

    T query(int target, int vertex, range borders) {
        if (borders.L() == borders.R()) {
            return tree[vertex].val;
        }

        int mid = borders.M();
        int left_vertex = vertex << 1;
        int right_vertex = vertex << 1 | 1;

        if (target <= mid) {
            return query(target, left_vertex, {borders.L(), mid});
        } else {
            return query(target, right_vertex, {mid + 1, borders.R()});
        }
    }

    T query(range query_range) {
        return query(query_range, 1, {1, n});
    }

    T query(range query_range, int vertex, range borders) {
        if (borders.L() > query_range.R() || borders.R() < query_range.L()) {
            return DEFAULT_VAL;
        }

        if (borders.L() >= query_range.L() && borders.R() <= query_range.R()) {
            return tree[vertex].val;
        }

        int mid = borders.M();
        int left_vertex = vertex << 1;
        int right_vertex = vertex << 1 | 1;
        T left_subtree = query(query_range, left_vertex, {borders.L(), mid});
        T right_subtree = query(query_range, right_vertex, {mid + 1, borders.R()});
        return query_operation(left_subtree, right_subtree);
    }
};