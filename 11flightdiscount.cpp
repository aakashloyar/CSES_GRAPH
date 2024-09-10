#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <climits>
#include <cstring>

using namespace std;

struct Pair {
    int n;
    long long w;
    Pair(int n, long long w) : n(n), w(w) {}
};

struct Compare {
    bool operator()(Pair const& a, Pair const& b) {
        return a.w > b.w;
    }
};

long long solve(vector<vector<Pair>>& list, int n, int m) {
    priority_queue<Pair, vector<Pair>, Compare> pq;
    priority_queue<Pair, vector<Pair>, Compare> pq2;

    pq.push(Pair(0, 0));
    vector<vector<long long>> dp(n, vector<long long>(2, LLONG_MAX));
    dp[0][0] = 0;

    while (!pq.empty()) {
        Pair p = pq.top();
        pq.pop();
        int curr = p.n;
        long long w = p.w;
        if(w>dp[curr][0]) continue;
        for (Pair& nextPair : list[curr]) {
            int next = nextPair.n;
            long long cw = nextPair.w;

            if (dp[next][0] > cw + w) {
                pq.push(Pair(next, cw + w));
                dp[next][0] = cw + w;
            }
            if (dp[next][1] > (cw / 2) + w) {
                pq2.push(Pair(next, (cw / 2) + w));
                dp[next][1] = (cw / 2) + w;
            }
        }
    }

    while (!pq2.empty()) {
        Pair p = pq2.top();
        pq2.pop();
        int curr = p.n;
        long long w = p.w;
        if(w>dp[curr][1]) continue;
        for (Pair& nextPair : list[curr]) {
            int next = nextPair.n;
            long long cw = nextPair.w;

            if (dp[next][1] > cw + w) {
                pq2.push(Pair(next, cw + w));
                dp[next][1] = cw + w;
            }
        }
    }

    return min(dp[n-1][0], dp[n-1][1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<Pair>> list(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        list[a - 1].emplace_back(b - 1, c);
    }

    long long ans = solve(list, n, m);
    cout << ans << "\n";

    return 0;
}
