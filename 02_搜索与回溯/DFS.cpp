/*
DFS
用途：遍历图中从起点可达的顶点
思路：访问当前点并标记，再递归访问尚未访问的邻居。
复杂度：时间 O(V+E)，额外空间 O(V)
注意：0 下标邻接表；有环也必须标记；长链递归可能爆栈，可改显式栈。
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
void dfs(int u, const vector<vector<int>>& g, vector<int>& vis, vector<int>& order) {
    vis[u]=1;
    order.push_back(u);
    for(int v:g[u])if(!vis[v])dfs(v, g, vis, order);
}
int main() {
    vector<vector<int>>g={{1, 2}, {0}, {0}, {}};
    vector<int>vis(4), order;
    dfs(0, g, vis, order);
    assert(order.size()==3 && !vis[3]);
    cout << "OK\n";
}
