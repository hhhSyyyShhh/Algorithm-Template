/*
树上最大权独立集
用途：树上选点，相邻两点不能同时选，最大化权值和
思路：dp[u][0/1] 表示不选/选 u；选 u 只能接孩子不选，否则取孩子两种状态较大值。
复杂度：时间 O(n)，空间 O(n)
注意：输入必须为树；允许一个点也不选；负权答案可以是 0；深树递归注意栈。
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
ll tree_independent(const vector<vector<int>>&g, const vector<ll>&w) {
    if(g.empty())return 0;
    vector<array<ll, 2>>dp(g.size());
    function<void(int, int)>go=[&](int u, int p) {
        dp[u]={0, w[u]};
        for(int v:g[u])if(v!=p) {
            go(v, u);
            dp[u][0]+=max(dp[v][0], dp[v][1]);
            dp[u][1]+=dp[v][0];
        }
    };
    go(0, -1);
    return max(dp[0][0], dp[0][1]);
}
int main() {
    assert(tree_independent({{1}, {0, 2}, {1}}, {2, 3, 4})==6);
    cout << "OK\n";
}
