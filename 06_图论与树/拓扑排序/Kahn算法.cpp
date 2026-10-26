/*
Kahn算法
用途：有向无环图的依赖排序及有向环检测
思路：把入度为 0 的点入队；删除该点的出边后，新入度为 0 的点继续入队。
复杂度：时间 O(V+E)，空间 O(V)
注意：结果个数不足 V 表示有环；拓扑序可能不唯一；空图的空序列合法。
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
vector<int> topo(const vector<vector<int>>&g) {
    vector<int>indeg(g.size()), ans;
    queue<int>q;
    for(auto&adj:g)for(int v:adj)++indeg[v];
    for(int i=0;i<(int)g.size();++i)if(!indeg[i])q.push(i);
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        ans.push_back(u);
        for(int v:g[u])if(--indeg[v]==0)q.push(v);
    }
    return ans;
}
int main() {
    assert(topo({{1}, {2}, {}})==vector<int>({0, 1, 2}));
    assert(topo({{1}, {0}}).size()<2);
    cout << "OK\n";
}
