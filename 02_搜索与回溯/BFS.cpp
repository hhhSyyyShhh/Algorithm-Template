/*
BFS
用途：无权图中起点到各点的最少边数
思路：队列按距离从近到远扩展；第一次发现某点时确定最短距离。
复杂度：时间 O(V+E)，空间 O(V)
注意：所有边权相同才可用普通 BFS 求最短路；入队就标记；-1 表示不可达。
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
vector<int> bfs(const vector<vector<int>>& g, int s) {
    vector<int>d(g.size(), -1);
    queue<int>q;
    d[s]=0;
    q.push(s);
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        for(int v:g[u])if(d[v]==-1) {
            d[v]=d[u]+1;
            q.push(v);
        }
    }
    return d;
}
int main() {
    assert((bfs({{1}, {2}, {}, {}}, 0)==vector<int>{0, 1, 2, -1}));
    cout << "OK\n";
}
