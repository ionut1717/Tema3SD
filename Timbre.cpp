#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

ifstream f("timbre.in");
ofstream g("timbre.out");

priority_queue<pair<int, int>> q;
priority_queue<int, vector<int>, greater<int>> costs;

int n, m, k;

int main() {
    f >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int mi_val, ci_val;
        f >> mi_val >> ci_val;
        q.push({mi_val, ci_val});
    }

    int rez = 0;

    while (n > 0) {
        while (!q.empty() && q.top().first >= n) {
            costs.push(q.top().second);
            q.pop();
        }

        if (costs.empty()) {
            break;
        }

        rez += costs.top();
        costs.pop();

        n -= k;
    }

    g << rez;

    f.close();
    g.close();

    return 0;
}