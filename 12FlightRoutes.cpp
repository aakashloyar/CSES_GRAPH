#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Pair {
    int n;
    long long w;
    Pair(int n, long long w) : n(n), w(w) {}
    bool operator<(const Pair& p) const {
        return w > p.w; // Reverse to make priority_queue a min-heap
    }
};

// Forward declarations
bool update(vector<long long>& dp, int k, long long w);
void print(const vector<long long>& arr);

void solve(vector<vector<Pair>>& list, int n, int m, int k) {
    priority_queue<Pair> pq;
    vector<vector<long long>> dp(n, vector<long long>(k, numeric_limits<long long>::max()));
    vector<vector<bool>> v(n, vector<bool>(k, false));
    
    pq.push(Pair(0, 0));
    dp[0][0] = 0;
    
    while (!pq.empty()) {
        Pair p = pq.top();
        pq.pop();
        int curr = p.n;
        long long w = p.w;
        
        bool is = false;
        for (int i = 0; i < k; ++i) {
            if (!v[curr][i] && dp[curr][i] == w) {
                v[curr][i] = true;
                is = true;
                break;
            }
        }
        if (!is) continue;
        
        for (const Pair& q : list[curr]) {
            int next = q.n;
            long long nw = w + q.w;
            if (update(dp[next], k, nw)) {
                pq.push(Pair(next, nw));
            }
        }
    }
    
    print(dp[n-1]);
}

bool update(vector<long long>& dp, int k, long long w) {
    for (int i = 0; i < k; ++i) {
        if (dp[i] > w) {
            for (int e = k-1; e > i; --e) {
                dp[e] = dp[e-1];
            }
            dp[i] = w;
            return true;
        }
    }
    return false;
}

void print(const vector<long long>& arr) {
    for (long long val : arr) {
        cout << val << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<vector<Pair>> list(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        list[a-1].emplace_back(b-1, c);
    }
    
    solve(list, n, m, k);
    
    return 0;
}
