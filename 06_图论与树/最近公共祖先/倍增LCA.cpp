/*
倍增LCA
用途：多次查询树上两点的最近公共祖先
思路：up[k][v] 是 v 的第 2^k 个祖先；先拉齐深度，再同步向上跳。
复杂度：预处理 O(n log n)，查询 O(log n)，空间 O(n log n)
注意：无向连通树、0 下标；根的祖先设为自己；用 BFS 建表避免预处理递归爆栈。
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
struct LCA {
    int LOG=1;
    vector<vector<int>>up;
    vector<int>dep;
    LCA(const vector<vector<int>>&g, int root=0) {
        int n=g.size();
        assert(n>0);
        while((1LL<<LOG)<=n)++LOG;
        up.assign(LOG, vector<int>(n, root));
        dep.assign(n, -1);
        queue<int>q;
        q.push(root);
        dep[root]=0;
        while(!q.empty()) {
            int u=q.front();
            q.pop();
            for(int v:g[u])if(dep[v]<0) {
                dep[v]=dep[u]+1;
                up[0][v]=u;
                q.push(v);
            }
        }
        for(int k=1;k<LOG;++k)for(int v=0;v<n;++v)up[k][v]=up[k-1][up[k-1][v]];
    }
    int query(int a, int b) {
        if(dep[a]<dep[b])swap(a, b);
        int diff=dep[a]-dep[b];
        for(int k=0;k<LOG;++k)if(diff>>k&1)a=up[k][a];
        if(a==b)return a;
        for(int k=LOG-1;k>=0;--k)if(up[k][a]!=up[k][b]) {
            a=up[k][a];
            b=up[k][b];
        }
        return up[0][a];
    }
};
int main() {
    LCA t({{1, 2}, {0, 3, 4}, {0}, {1}, {1}});
    assert(t.query(3, 4)==1);
    assert(t.query(3, 2)==0);
    cout << "OK\n";
}
