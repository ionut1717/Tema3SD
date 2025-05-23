#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream f("bleach.in");
ofstream g("bleach.out");

bool check(int starting_power, const vector<int>& enemy_powers) {
    long long ichigo = starting_power;
    for (const auto& power : enemy_powers) {
        if (ichigo < power) return false;
        ichigo += power;
    }
    return true;
}

int main() {
    int n,k;
    f >> n >> k;

    vector<int> enemy_powers(n);
    for (int i = 0; i < n; ++i) {
        f >> enemy_powers[i];
    }

    sort(enemy_powers.begin(), enemy_powers.end());

    int low = 1, high = 2'000'000'000, result = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid, enemy_powers)) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    g << result << '\n';

    return 0;
}
