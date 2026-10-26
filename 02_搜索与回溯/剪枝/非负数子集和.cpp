/*
非负数子集和
用途：判断能否选一些非负整数使和为 target
思路：每个数选或不选；当前和太大、或加上剩余全部仍不够时提前返回。
复杂度：最坏时间 O(2^n)，空间 O(n)
注意：要求所有数字和 target 非负；负数会破坏这两种剪枝的正确性。
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
bool subset_sum(const vector<int>& a, ll target) {
    int n=a.size();
    vector<ll>suf(n+1);
    for(int i=n-1;i>=0;--i)suf[i]=suf[i+1]+a[i];
    function<bool(int, ll)>go=[&](int i, ll sum) {
        if(sum==target)return true;
        if(i==n || sum>target || sum+suf[i]<target)return false;
        return go(i+1, sum+a[i]) || go(i+1, sum);
    };
    return go(0, 0);
}
int main() {
    assert(subset_sum({2, 3, 7}, 5));
    assert(!subset_sum({2, 3, 7}, 6));
    cout << "OK\n";
}
