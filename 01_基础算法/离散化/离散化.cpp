/*
离散化
用途：将稀疏的大数映射成紧凑排名
思路：复制、排序、去重，再二分求排名；保留大小关系。
复杂度：预处理 O(n log n)，单次排名 O(log n)，空间 O(n)
注意：不保留数值间距离；只对原先收集过的数求精确编号。
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
vector<ll> compress(vector<ll> a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    return a;
}
int rank_of(const vector<ll>& values, ll x) {
    return lower_bound(values.begin(), values.end(), x)-values.begin();
}
int main() {
    auto v=compress({100, 5, 100, 900});
    assert(rank_of(v, 100)==1);
    cout << "OK\n";
}
