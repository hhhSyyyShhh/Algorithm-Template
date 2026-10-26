/*
差分
用途：多次区间加，最后一次性恢复数组
思路：差分保存相邻变化；给 [l,r] 加 x，只修改 d[l]+=x 与 d[r+1]-=x。
复杂度：初始化和恢复 O(n)，每次修改 O(1)，空间 O(n)
注意：离线处理：所有修改完成后再恢复；不适合每次修改后立即查询区间和。
学习方式：先读说明，再手算 main 中的例子，最后遮住实现自己重写。
*/
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
vector<ll> range_add(vector<ll> a, const vector<tuple<int, int, ll>>& ops) {
    int n=a.size();
    vector<ll>d(n+1);
    for(int i=0;i<n;++i)d[i]=a[i]-(i?a[i-1]:0);
    for(auto [l, r, x]:ops) {
        d[l]+=x;
        d[r+1]-=x;
    }
    ll cur=0;
    for(int i=0;i<n;++i) {
        cur+=d[i];
        a[i]=cur;
    }
    return a;
}
int main() {
    assert((range_add({1, 2, 3}, {{0, 1, 5}})==vector<ll>{6, 7, 3}));
    cout << "OK\n";
}
