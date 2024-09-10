#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void solve(vector<vector<long long>>& dp, vector<vector<int>>& que, int n, int m, int q) {
    for (int via = 0; via < n; via++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][via] != LLONG_MAX && dp[via][j] != LLONG_MAX) {
                    dp[i][j] = min(dp[i][j], dp[i][via] + dp[via][j]);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[i][j] == LLONG_MAX) dp[i][j] = -1;
        }
    }
    vector<long long> res(q);
    for (int i = 0; i < q; i++) {
        res[i] = dp[que[i][0]][que[i][1]];
    }
    for (long long val : res) {
        cout << val << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<long long>> dp(n, vector<long long>(n, LLONG_MAX));
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--; b--; // Convert to 0-based indexing
        dp[a][b] = min((long long)w, dp[a][b]);
        dp[b][a] = min((long long)w, dp[b][a]);
    }
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    }
    vector<vector<int>> que(q, vector<int>(2));
    for (int i = 0; i < q; i++) {
        cin >> que[i][0] >> que[i][1];
        que[i][0]--; que[i][1]--; // Convert to 0-based indexing
    }
    solve(dp, que, n, m, q);
    return 0;
}
