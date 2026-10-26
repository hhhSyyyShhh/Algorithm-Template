/*
有序数组两数之和
用途：在升序数组中找两个不同位置，使和等于目标
思路：和小就左端右移，和大就右端左移；每步排除不可能的组合。
复杂度：时间 O(n)，空间 O(1)
注意：输入必须升序；返回下标；找不到返回 {-1,-1}。
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
pair<int, int> two_sum(const vector<int>& a, ll target) {
    int l=0, r=(int)a.size()-1;
    while(l<r) {
        ll s=(ll)a[l]+a[r];
        if(s==target)return {l, r};
        if(s<target)++l;
        else --r;
    }
    return {-1, -1};
}
int main() {
    assert(two_sum({1, 2, 4, 7}, 6)==make_pair(1, 2));
    assert(two_sum({}, 0)==make_pair(-1, -1));
    cout << "OK\n";
}
