#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int MOD = 1e9 + 7;

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

void dijkstra(const vector<vector<Pair>>& list, vector<long long>& dp, int n) {
    priority_queue<Pair, vector<Pair>, Compare> pq;
    pq.push(Pair(0, 0));
    while (!pq.empty()) {
        Pair p = pq.top();
        pq.pop();
        int curr = p.n;
        long long cw = p.w;
        if (curr == n - 1) continue;
        if (dp[curr] < cw) continue;
        for (const Pair& pn : list[curr]) {
            int next = pn.n;
            long long nw = cw + pn.w;
            if (dp[next] <= nw) continue;
            dp[next] = nw;
            pq.push(Pair(next, nw));
        }
    }
}

long long func1(const vector<vector<Pair>>& list, vector<long long>& dp, const vector<long long>& min, int n, long long w, int curr) {
    if (curr == n - 1) return 1;
    if (dp[curr] != -1) return dp[curr];
    long long sum = 0;
    for (const Pair& p : list[curr]) {
        int next = p.n;
        long long nw = w + p.w;
        if (nw != min[next]) continue;
        long long x = func1(list, dp, min, n, nw, next);
        sum += x;
        sum %= MOD;
    }
    dp[curr] = sum;
    return sum;
}

long long func2(const vector<vector<Pair>>& list, vector<long long>& dp, const vector<long long>& wei, int n, long long w, int curr) {
    if (curr == n - 1) return 0;
    if (dp[curr] != -1) return dp[curr];
    long long sum = LLONG_MAX;
    for (const Pair& p : list[curr]) {
        int next = p.n;
        long long nw = w + p.w;
        if (nw != wei[next]) continue;
        long long x = func2(list, dp, wei, n, nw, next);
        sum = min(sum, x);
    }
    if (sum != LLONG_MAX) sum++;
    dp[curr] = sum;
    return dp[curr];
}

long long func3(const vector<vector<Pair>>& list, vector<long long>& dp, const vector<long long>& wei, int n, long long w, int curr) {
    if (curr == n - 1) return 0;
    if (dp[curr] != LLONG_MIN) return dp[curr];
    long long sum = -1;
    for (const Pair& p : list[curr]) {
        int next = p.n;
        long long nw = w + p.w;
        if (nw != wei[next]) continue;
        long long x = func3(list, dp, wei, n, nw, next);
        sum = max(sum, x);
    }
    if (sum != -1) sum++;
    dp[curr] = sum;
    return dp[curr];
}

void solve(const vector<vector<Pair>>& list, int n) {
    vector<long long> dp(n, LLONG_MAX);
    vector<long long> dp2(n, -1);
    vector<long long> dp3(n, -1);
    vector<long long> dp4(n, LLONG_MIN);
    
    dijkstra(list, dp, n);
    long long a = dp[n - 1];
    long long b = func1(list, dp2, dp, n, 0, 0);
    long long c = func2(list, dp3, dp, n, 0, 0);
    long long d = func3(list, dp4, dp, n, 0, 0);
    cout << a << " " << b << " " << c << " " << d << endl;
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
    solve(list, n);

    return 0;
}
