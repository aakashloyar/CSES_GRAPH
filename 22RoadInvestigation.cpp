#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
using namespace std;

const int MOD = 1e9 + 7;

struct Pair {
    int n;
    long long w;
    Pair(int n, long long w) : n(n), w(w) {}
};

struct PC {
    bool operator()(const Pair& a, const Pair& b) {
        return a.w > b.w;
    }
};

void solve(const vector<vector<Pair>>& list, int n) {
    auto dijkstra = [&](const vector<vector<Pair>>& list, int n) -> long long {
        vector<bool> v(n, false);
        long long sum = 0;
        priority_queue<Pair, vector<Pair>, PC> pq;
        pq.push(Pair(0, 0));
        while (!pq.empty()) {
            Pair p = pq.top();
            pq.pop();
            int curr = p.n;
            long long cw = p.w;
            if (v[curr]) continue;
            v[curr] = true;
            sum += cw;
            const vector<Pair>& internal = list[curr];
            for (const Pair& pn : internal) {
                int next = pn.n;
                long long nw = pn.w;
                if (!v[next]) {
                    pq.push(Pair(next, nw));
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (!v[i]) return -1;
        }
        return sum;
    };

    long long a = dijkstra(list, n);
    if (a == -1) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    cout << a << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Pair>> list(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        list[a].emplace_back(b, c);
        list[b].emplace_back(a, c);
    }

    solve(list, n);

    return 0;
}
