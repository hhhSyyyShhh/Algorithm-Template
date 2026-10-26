/*
邻接表
用途：表示有向或无向带权图
思路：g[u] 保存从 u 出发的边；无向边需要添加两个方向。
复杂度：建图 O(V+E)，空间 O(V+E)
注意：0 下标；普通邻接矩阵需要 O(V²) 空间；重边是否保留由题目决定。
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
struct Edge {
    int to;
    ll weight;
};
void add_edge(vector<vector<Edge>>&g, int u, int v, ll w, bool directed) {
    g[u].push_back({v, w});
    if(!directed)g[v].push_back({u, w});
}
int main() {
    vector<vector<Edge>>g(3);
    add_edge(g, 0, 1, 5, false);
    assert(g[1][0].to==0);
    cout << "OK\n";
}
