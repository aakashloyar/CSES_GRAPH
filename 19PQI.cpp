#include <bits/stdc++.h>
using namespace std;

void solve(vector<vector<int>> &arr, vector<pair<int, int>> &queries, int n, int m, int q) {
    vector<int> res(q);
    for (int i = 0; i < q; ++i) {
        int ans = queries[i].first, k = queries[i].second;
        int x = 0;
        while (k != 0) {
            int b = k & 1;
            if (b != 0) ans = arr[ans][x];
            x++;
            k >>= 1;
        }
        res[i] = ans + 1;
    }
    for (int i = 0; i < q; ++i) {
        cout << res[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    int m = 31;
    vector<vector<int>> arr(n, vector<int>(m));
    
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        arr[i][0] = a - 1;
    }

    for (int j = 1; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            arr[i][j] = arr[arr[i][j - 1]][j - 1];
        }
    }

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        queries[i] = {a - 1, b};
    }
    
    solve(arr, queries, n, m, q);
    
    return 0;
}
