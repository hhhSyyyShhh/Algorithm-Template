/*
单调栈
用途：找每个元素右侧第一个严格更大的元素下标
思路：栈保存尚未找到答案的位置；新元素出现时，依次解决比它小的栈顶。
复杂度：摊还时间 O(n)，空间 O(n)
注意：严格更大用 < 弹栈；没有答案返回 -1；相等元素不弹出。
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
vector<int> next_greater(const vector<int>&a) {
    vector<int>ans(a.size(), -1);
    stack<int>s;
    for(int i=0;i<(int)a.size();++i) {
        while(!s.empty() && a[s.top()]<a[i]) {
            ans[s.top()]=i;
            s.pop();
        }
        s.push(i);
    }
    return ans;
}
int main() {
    assert(next_greater({2, 2, 3, 1})==vector<int>({2, 2, -1, -1}));
    cout << "OK\n";
}
