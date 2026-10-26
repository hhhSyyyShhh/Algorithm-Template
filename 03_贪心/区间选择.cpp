/*
区间选择
用途：选最多个互不重叠的区间
思路：按结束时间从小到大排序，每次选能接上的区间；结束越早给后续留下越大空间。
复杂度：时间 O(n log n)，排序后扫描 O(n)
注意：这里区间按 [l,r) 理解，端点相接允许；要求 l<r；其他贪心需独立证明。
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
int max_intervals(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end(), [](auto x, auto y) {
        return x.second<y.second;
    });
    ll end=LLONG_MIN;
    int count=0;
    for(auto [l, r]:a)if(l>=end) {
        ++count;
        end=r;
    }
    return count;
}
int main() {
    assert(max_intervals({{1, 3}, {2, 4}, {3, 5}, {5, 6}})==3);
    cout << "OK\n";
}
