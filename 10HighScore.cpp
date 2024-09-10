#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll solve(vector<vector<int>>& vect,int n,int m) {
    ll dp[n];
    for(int i=0;i<n;i++) dp[i]=LONG_MIN;
    dp[0]=0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            int u=vect[j][0],v=vect[j][1],x=vect[j][2];
            if(dp[u]!=LONG_MIN) {
                dp[v]=max(dp[u]+x,dp[v]);
            }
        }
    }
    ll prev=dp[n-1];
    for(int i=0;i<m;i++) {
        int u=vect[i][0],v=vect[i][1],x=vect[i][2];
        if(dp[u]!=LONG_MIN) {
            dp[v]=max(dp[u]+x,dp[v]);
        }
    }
    if(dp[n-1]!=prev) return -1;
    return prev;
}

int main() {
    int n,m;
    cin>>n>>m;
    vector<vector<int>> vect(m, vector<int>(3));
    for(int i=0;i<m;i++) {
        int a,b,x;
        cin>>a>>b>>x;
        a--;
        b--;
        vect[i][0]=a;
        vect[i][1]=b;
        vect[i][2]=x;

    }
    cout<<solve(vect,n,m)<<endl;

}
