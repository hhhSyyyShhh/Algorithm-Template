/*
STL栈队列
用途：后进先出与先进先出
思路：stack 对应撤销和递归；queue 对应排队和分层遍历。
复杂度：基本操作 O(1)，空间 O(n)
注意：访问 top/front 或 pop 前先判断 empty；pop 不返回元素。
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
vector<int> reverse_by_stack(const vector<int>& a) {
    stack<int>s;
    for(int x:a)s.push(x);
    vector<int>ans;
    while(!s.empty()) {
        ans.push_back(s.top());
        s.pop();
    }
    return ans;
}
int main() {
    assert(reverse_by_stack({1, 2, 3})==vector<int>({3, 2, 1}));
    queue<int>q;
    q.push(4);
    q.push(5);
    q.pop();
    assert(q.front()==5);
    cout << "OK\n";
}
