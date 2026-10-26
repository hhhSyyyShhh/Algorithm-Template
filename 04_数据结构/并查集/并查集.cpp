/*
并查集
用途：维护集合合并与连通性
思路：父指针代表集合；路径压缩和按大小合并降低树高。
复杂度：单次均摊 O(α(n))，初始化和空间 O(n)
注意：0 下标；不能直接支持删边；有向图可达性不能用普通并查集代替。
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
int main() {
    DSU d(4);
    assert(d.unite(0, 1));
    assert(!d.unite(1, 0));
    assert(d.find(0)==d.find(1));
    cout << "OK\n";
}
