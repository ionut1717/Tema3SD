#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Node {
    int min_val;
    int max_val;
    int min_next_occ;
};

vector<int> a;
vector<int> duplicate;
vector<Node> tree;
int n;

Node merge_nodes(const Node& left_child, const Node& right_child) {
    Node parent;
    parent.min_val = min(left_child.min_val, right_child.min_val);
    parent.max_val = max(left_child.max_val, right_child.max_val);
    parent.min_next_occ = min(left_child.min_next_occ, right_child.min_next_occ);
    return parent;
}

void build(int node_idx, int start, int end) {
    if (start == end) {
        tree[node_idx].min_val = a[start];
        tree[node_idx].max_val = a[start];
        tree[node_idx].min_next_occ = duplicate[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node_idx, start, mid);
        build(2 * node_idx + 1, mid + 1, end);
        tree[node_idx] = merge_nodes(tree[2 * node_idx], tree[2 * node_idx + 1]);
    }
}

Node query(int node_idx, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return {100002, 0, 100002};
    }
    if (l <= start && end <= r) {
        return tree[node_idx];
    }
    int mid = (start + end) / 2;
    Node p1 = query(2 * node_idx, start, mid, l, r);
    Node p2 = query(2 * node_idx + 1, mid + 1, end, l, r);
    return merge_nodes(p1, p2);
}

int main() {
    cin >> n;

    a.resize(n + 1);
    duplicate.resize(n + 1, n + 1);
    map<int, int> last_pos;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (last_pos.count(a[i])) {
            duplicate[last_pos[a[i]]] = i;
        }
        last_pos[a[i]] = i;
    }

    tree.resize(4 * n);
    build(1, 1, n);

    int Q;
    cin >> Q;


    for (int q_idx = 0; q_idx < Q; ++q_idx) {
        int x, y;
        cin >> x >> y;

        Node res = query(1, 1, n, x, y);

        int min_val_interval = res.min_val;
        int max_val_interval = res.max_val;
        int min_next_occ_interval = res.min_next_occ;

        bool are_distincte = (min_next_occ_interval > y);
        bool lungime_ok = (max_val_interval - min_val_interval + 1 == (y - x + 1));

        if (are_distincte && lungime_ok) {
            cout<<"1";
        } else {
             cout<<"0";
        }
    }


    return 0;
}