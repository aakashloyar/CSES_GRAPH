#include <bits/stdc++.h>
using namespace std;

void solve(vector<vector<int>>& list, int n);
int func1(vector<vector<int>>& list, vector<vector<int>>& dp, int curr);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> list(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        list[a - 1].push_back(b - 1);
    }

    solve(list, n);
    return 0;
}

void solve(vector<vector<int>>& list, int n) {
    vector<vector<int>> dp(n, vector<int>(2, -1));
    dp[n - 1][0] = 1;
    int a = func1(list, dp, 0);
    if (a == -1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    cout << a << "\n";
    int curr = 0;
    while (curr != -1) {
        cout << curr + 1 << " ";
        curr = dp[curr][1];
    }
    cout << "\n";
}

int func1(vector<vector<int>>& list, vector<vector<int>>& dp, int curr) {
    if (dp[curr][0] != -1) return dp[curr][0];

    for (int next : list[curr]) {
        int x = func1(list, dp, next);
        if (x > dp[curr][0]) {
            dp[curr][0] = x;
            dp[curr][1] = next;
        }
    }

    if (dp[curr][0] >= 0) dp[curr][0]++;
    return dp[curr][0];
}
