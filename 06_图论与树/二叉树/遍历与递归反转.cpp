/*
遍历与递归反转
用途：前中后序、层序遍历，原地反转二叉树
思路：前中后指根在左子树与右子树访问顺序中的位置；反转时交换每个节点的左右孩子。
复杂度：时间 O(n)，递归空间 O(h)，层序队列空间 O(n)
注意：-1 表示空节点；vector 下标代表节点，不是节点值；反转会修改原树。
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
struct Node {
    int val, left=-1, right=-1;
};
void traverse(const vector<Node>&t, int u, vector<int>&pre, vector<int>&in, vector<int>&post) {
    if(u==-1)return;
    pre.push_back(t[u].val);
    traverse(t, t[u].left, pre, in, post);
    in.push_back(t[u].val);
    traverse(t, t[u].right, pre, in, post);
    post.push_back(t[u].val);
}
vector<int> level_order(const vector<Node>&t, int root) {
    vector<int>ans;
    if(root==-1)return ans;
    queue<int>q;
    q.push(root);
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        ans.push_back(t[u].val);
        if(t[u].left!=-1)q.push(t[u].left);
        if(t[u].right!=-1)q.push(t[u].right);
    }
    return ans;
}
void invert(vector<Node>&t, int u) {
    if(u==-1)return;
    swap(t[u].left, t[u].right);
    invert(t, t[u].left);
    invert(t, t[u].right);
}
int main() {
    vector<Node>t={{1, 1, 2}, {2}, {3}};
    vector<int>a, b, c;
    traverse(t, 0, a, b, c);
    assert(a==vector<int>({1, 2, 3}));
    assert(b==vector<int>({2, 1, 3}));
    assert(c==vector<int>({2, 3, 1}));
    invert(t, 0);
    assert(level_order(t, 0)==vector<int>({1, 3, 2}));
    cout << "OK\n";
}
