/*
Kruskal
用途：无向带权图连接所有顶点的最小总权
思路：按边权从小到大尝试，只有连接不同集合的边才加入；并查集避免成环。
复杂度：时间 O(E log E)，空间 O(V+E)
注意：求的是生成树，不是最短路；返回 bool 为 false 表示图不连通，此时总权是生成森林权。
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
struct DSU {
    vector<int>p, sz;
    DSU(int n):p(n), sz(n, 1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x]==x?x:p[x]=find(p[x]);
    }
    bool unite(int a, int b) {
        a=find(a);
        b=find(b);
        if(a==b)return false;
        if(sz[a]<sz[b])swap(a, b);
        p[b]=a;
        sz[a]+=sz[b];
        return true;
    }
};
pair<bool, ll> kruskal(int n, vector<tuple<ll, int, int>>edges) {
    sort(edges.begin(), edges.end());
    DSU d(n);
    ll sum=0;
    int count=0;
    for(auto [w, u, v]:edges)if(d.unite(u, v)) {
        sum+=w;
        ++count;
    }
    return {n==0 || count==n-1, sum};
}
int main() {
    assert(kruskal(3, {{1, 0, 1}, {3, 0, 2}, {2, 1, 2}})==make_pair(true, 3LL));
    assert(!kruskal(3, {{1, 0, 1}}).first);
    cout << "OK\n";
}
