#include <bits/stdc++.h>
using namespace std;

void solve(vector<vector<int>>& list, vector<int>& ind, int n, int m) {
    vector<int> res;
    queue<int> q;
    for (int i = 0; i < n; i++) 
        if (ind[i] == 0) 
            q.push(i);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        res.push_back(curr + 1);
        for (int next : list[curr]) {
            ind[next]--;
            if (ind[next] == 0) 
                q.push(next);
        }
    }

    if (res.size() != n) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    for (int i = 0; i < n; i++) 
        cout << res[i] << " ";
    cout << "\n";
}

int func1(vector<vector<int>>& list, stack<int>& s, vector<int>& v, int curr) {
    if (v[curr] == 1) return 0;
    v[curr] = -1;
    for (int next : list[curr]) {
        if (v[next] == -1) return -1;
        int res = func1(list, s, v, next);
        if (res == -1) return res;
    }
    v[curr] = 1;
    s.push(curr);
    return 0;
}

void solve2(vector<vector<int>>& list, int n, int m) {
    stack<int> s;
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++) {
        if (v[i] == 0) {
            int res = func1(list, s, v, i);
            if (res == -1) {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
    }
    while (!s.empty()) {
        cout << s.top() + 1 << " ";
        s.pop();
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> list(n);
    vector<int> ind(n, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        ind[b]++;
        list[a].push_back(b);
    }

    solve2(list, n, m);

    return 0;
}
