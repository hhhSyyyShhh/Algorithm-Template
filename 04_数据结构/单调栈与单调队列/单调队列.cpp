/*
单调队列
用途：固定长度滑动窗口最大值
思路：双端队列保存下标，值从队首到队尾递减；先清理过期下标再维护单调性。
复杂度：摊还时间 O(n)，空间 O(k)
注意：要求 1<=k<=n；存下标才能判断元素是否离开窗口。
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
vector<int> window_max(const vector<int>&a, int k) {
    assert(k>=1 && k<=(int)a.size());
    deque<int>q;
    vector<int>ans;
    for(int i=0;i<(int)a.size();++i) {
        while(!q.empty() && q.front()<=i-k)q.pop_front();
        while(!q.empty() && a[q.back()]<=a[i])q.pop_back();
        q.push_back(i);
        if(i>=k-1)ans.push_back(a[q.front()]);
    }
    return ans;
}
int main() {
    assert(window_max({1, 3, -1, -3, 5, 3, 6, 7}, 3)==vector<int>({3, 3, 5, 5, 6, 7}));
    cout << "OK\n";
}
