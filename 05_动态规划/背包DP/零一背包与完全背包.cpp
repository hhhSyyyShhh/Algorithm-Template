/*
零一背包与完全背包
用途：容量内最大价值，每件一次或无限次
思路：dp[c] 是容量不超过 c 的最大价值；01 倒序避免重复用，完全正序允许重复用。
复杂度：时间 O(nW)，空间 O(W)
注意：重量为正；允许不选且不要求装满；恰好装满需改初值，不能直接套用。
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
ll knapsack(const vector<int>&w, const vector<int>&v, int W, bool unlimited) {
    vector<ll>dp(W+1);
    for(int i=0;i<(int)w.size();++i) {
        assert(w[i]>0);
        if(unlimited) {
            for(int c=w[i];c<=W;++c)dp[c]=max(dp[c], dp[c-w[i]]+v[i]);
        }
        else {
            for(int c=W;c>=w[i];--c)dp[c]=max(dp[c], dp[c-w[i]]+v[i]);
        }
    }
    return dp[W];
}
int main() {
    assert(knapsack({2, 3}, {3, 4}, 4, false)==4);
    assert(knapsack({2, 3}, {3, 4}, 4, true)==6);
    cout << "OK\n";
}
