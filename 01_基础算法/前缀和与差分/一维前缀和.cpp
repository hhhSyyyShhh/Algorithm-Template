/*
一维前缀和
用途：静态数组多次区间求和
思路：s[i] 保存前 i 个数的和；闭区间 [l,r] 的和是 s[r+1]-s[l]。
复杂度：预处理 O(n)，查询 O(1)，空间 O(n)
注意：原数组下标从 0 开始；查询要求 0<=l<=r<n；求和用 long long。
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
vector<ll> prefix(const vector<int>& a) {
    vector<ll> s(a.size()+1, 0);
    for (size_t i=0;i<a.size();++i) s[i+1]=s[i]+a[i];
    return s;
}
ll query(const vector<ll>& s, int l, int r) {
    return s[r+1]-s[l];
}
int main() {
    auto s=prefix({2, 3, -1, 5});
    assert(query(s, 1, 3)==7);
    assert(query(s, 0, 0)==2);
    cout << "OK\n";
}
