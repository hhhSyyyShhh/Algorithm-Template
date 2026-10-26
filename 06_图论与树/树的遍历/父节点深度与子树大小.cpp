/*
父节点深度与子树大小
用途：有根树的基本信息预处理
思路：DFS 从根向下确定父亲、深度，回溯时将孩子子树大小累加。
复杂度：时间 O(n)，空间 O(n)
注意：无向树中跳过父亲即可；一般图还需要 visited，不能直接套本模板。
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
void tree_dfs(int u, int p, const vector<vector<int>>&g, vector<int>&parent, vector<int>&depth, vector<int>&sz) {
    parent[u]=p;
    sz[u]=1;
    for(int v:g[u])if(v!=p) {
        depth[v]=depth[u]+1;
        tree_dfs(v, u, g, parent, depth, sz);
        sz[u]+=sz[v];
    }
}
int main() {
    vector<vector<int>>g={{1, 2}, {0}, {0}};
    vector<int>p(3), d(3), s(3);
    tree_dfs(0, -1, g, p, d, s);
    assert(s[0]==3 && d[2]==1 && p[2]==0);
    cout << "OK\n";
}
