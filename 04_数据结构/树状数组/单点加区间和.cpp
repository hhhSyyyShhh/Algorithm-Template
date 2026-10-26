/*
单点加区间和
用途：动态单点加，查询区间和
思路：bit[i] 管辖末尾 lowbit(i) 个元素；更新向上跳，查询向前跳。
复杂度：更新查询 O(log n)，空间 O(n)
注意：此模板从 1 开始编号；add(0,...) 会死循环；求任意区间和用前缀相减。
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
struct Fenwick {
    int n;
    vector<ll>bit;
    Fenwick(int n):n(n), bit(n+1) {
    }
    void add(int i, ll x) {
        assert(i>=1 && i<=n);
        for(;i<=n;i+=i&-i)bit[i]+=x;
    }
    ll prefix(int i)const{ll s=0;
    for(;i>0;i-=i&-i)s+=bit[i];
    return s;
    }
    ll sum(int l, int r)const{return prefix(r)-prefix(l-1);
    }
};
int main() {
    Fenwick f(3);
    f.add(1, 2);
    f.add(2, 5);
    assert(f.sum(1, 2)==7);
    f.add(2, -3);
    assert(f.sum(2, 3)==2);
    cout << "OK\n";
}
