/*
下界二分
用途：查找第一个大于等于 x 的位置
思路：维护左闭右开区间 [l,r)，答案始终在边界范围内；根据中点缩小范围。
复杂度：时间 O(log n)，空间 O(1)
注意：数组必须升序；返回 n 表示不存在，不可直接访问 a[n]。
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
int lower_bound_index(const vector<int>& a, int x) {
    int l=0, r=a.size();
    while(l<r) {
        int mid=l+(r-l)/2;
        if(a[mid]>=x)r=mid;
        else l=mid+1;
    }
    return l;
}
int main() {
    assert(lower_bound_index({1, 3, 3, 7}, 3)==1);
    assert(lower_bound_index({1, 3}, 9)==2);
    assert(lower_bound_index({}, 1)==0);
    cout << "OK\n";
}
