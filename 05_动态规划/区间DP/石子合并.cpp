/*
石子合并
用途：直线排列石堆每次合并相邻两堆，求最小总代价
思路：dp[l][r] 枚举最后一次合并的分割点 k；左右最优代价加整个区间重量。
复杂度：时间 O(n³)，空间 O(n²)
注意：非环形版本；每次合并代价为两堆总重量；先算短区间再算长区间。
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
ll merge_stones(const vector<int>&a) {
    int n=a.size();
    if(!n)return 0;
    vector<ll>s(n+1);
    for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];
    vector<vector<ll>>dp(n, vector<ll>(n));
    for(int len=2;len<=n;++len)for(int l=0;l+len<=n;++l) {
        int r=l+len-1;
        dp[l][r]=LLONG_MAX/4;
        for(int k=l;k<r;++k)dp[l][r]=min(dp[l][r], dp[l][k]+dp[k+1][r]+s[r+1]-s[l]);
    }
    return dp[0][n-1];
}
int main() {
    assert(merge_stones({1, 2, 3})==9);
    assert(merge_stones({5})==0);
    cout << "OK\n";
}
