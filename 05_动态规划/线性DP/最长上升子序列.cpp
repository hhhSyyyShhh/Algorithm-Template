/*
最长上升子序列
用途：最长严格上升子序列长度，入门 O(n²) 版
思路：dp[i] 是以 i 结尾的最优长度；从所有更小的前驱 j 转移。
复杂度：时间 O(n²)，空间 O(n)
注意：子序列允许不连续；严格上升用 <；空数组答案 0。
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
int lis(const vector<int>&a) {
    vector<int>dp(a.size(), 1);
    int ans=0;
    for(int i=0;i<(int)a.size();++i) {
        for(int j=0;j<i;++j)if(a[j]<a[i])dp[i]=max(dp[i], dp[j]+1);
        ans=max(ans, dp[i]);
    }
    return ans;
}
int main() {
    assert(lis({3, 1, 2, 2, 5})==3);
    assert(lis({})==0);
    cout << "OK\n";
}
