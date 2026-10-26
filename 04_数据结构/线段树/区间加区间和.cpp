/*
区间加区间和
用途：区间整体加，区间求和
思路：节点记录区间和，lazy 表示尚未传给孩子的增量；下探前下传，回溯时合并。
复杂度：建树 O(n)，每次操作 O(log n)，空间 O(n)
注意：0 下标闭区间；非空数组；lazy 增量对和的贡献是增量乘区间长度。
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
struct SegTree {
    int n;
    vector<ll>s, lazy;
    SegTree(const vector<ll>&a):n(a.size()), s(4*n), lazy(4*n) {
        assert(n>0);
        build(1, 0, n-1, a);
    }
    void build(int p, int l, int r, const vector<ll>&a) {
        if(l==r) {
            s[p]=a[l];
            return;
        }
        int m=(l+r)/2;
        build(p*2, l, m, a);
        build(p*2+1, m+1, r, a);
        s[p]=s[p*2]+s[p*2+1];
    }
    void apply(int p, int l, int r, ll x) {
        s[p]+=x*(r-l+1);
        lazy[p]+=x;
    }
    void push(int p, int l, int r) {
        int m=(l+r)/2;
        apply(p*2, l, m, lazy[p]);
        apply(p*2+1, m+1, r, lazy[p]);
        lazy[p]=0;
    }
    void add(int p, int l, int r, int ql, int qr, ll x) {
        if(ql<=l && r<=qr) {
            apply(p, l, r, x);
            return;
        }
        push(p, l, r);
        int m=(l+r)/2;
        if(ql<=m)add(p*2, l, m, ql, qr, x);
        if(qr>m)add(p*2+1, m+1, r, ql, qr, x);
        s[p]=s[p*2]+s[p*2+1];
    }
    ll sum(int p, int l, int r, int ql, int qr) {
        if(ql<=l && r<=qr)return s[p];
        push(p, l, r);
        int m=(l+r)/2;
        ll ans=0;
        if(ql<=m)ans+=sum(p*2, l, m, ql, qr);
        if(qr>m)ans+=sum(p*2+1, m+1, r, ql, qr);
        return ans;
    }
    void add(int l, int r, ll x) {
        add(1, 0, n-1, l, r, x);
    }
    ll sum(int l, int r) {
        return sum(1, 0, n-1, l, r);
    }
};
int main() {
    SegTree t({1, 2, 3, 4});
    t.add(0, 3, 2);
    t.add(1, 2, -1);
    assert(t.sum(0, 3)==16);
    assert(t.sum(1, 1)==3);
    cout << "OK\n";
}
