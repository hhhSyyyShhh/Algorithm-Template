/*
旅行商路径
用途：从 0 出发访问所有点一次后回到 0，求最小花费
思路：dp[mask][u] 表示访问集合 mask、结束在 u 的最小代价；添加一个未访问点。
复杂度：时间 O(2^n*n²)，空间 O(2^n*n)
注意：演示完整非负权矩阵；n>=1，通常 n<=20 且要看内存；不处理缺边，缺边需显式跳过。
学习方式：先读说明，再手算 main 中的例子，最后遮住实现自己重写。
*/
#include <deque>
#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
ll tsp(const vector<vector<int>>&c) {
    int n=c.size();
    assert(n>=1 && n<=20);
    const ll INF=LLONG_MAX/4;
    vector<vector<ll>>dp(1<<n, vector<ll>(n, INF));
    dp[1][0]=0;
    for(int mask=1;mask<(1<<n);++mask)for(int u=0;u<n;++u)if(dp[mask][u]<INF) {
        for(int v=0;v<n;++v)if(!(mask>>v&1))
        dp[mask|1<<v][v]=min(dp[mask|1<<v][v], dp[mask][u]+c[u][v]);
    }
    ll ans=INF;
    for(int u=0;u<n;++u)ans=min(ans, dp[(1<<n)-1][u]+c[u][0]);
    return ans;
}
int main() {
    assert(tsp({{0, 2, 4}, {2, 0, 3}, {4, 3, 0}})==9);
    cout << "OK\n";
}
