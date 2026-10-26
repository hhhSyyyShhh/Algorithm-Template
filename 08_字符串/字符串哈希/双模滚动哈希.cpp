/*
双模滚动哈希
用途：快速比较子串是否可能相同
思路：多项式前缀哈希；子串哈希减去前缀乘相应次幂，对两个模数各算一次。
复杂度：预处理 O(n)，查询 O(1)，空间 O(n)
注意：双哈希仍有碰撞概率，不能视作数学上的绝对相等；区间 [l,r)；跨串须用同一参数。
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
struct Hash {
    static constexpr ll M1=1000000007, M2=1000000009, B=131;
    vector<ll>h1, h2, p1, p2;
    Hash(const string&s):h1(s.size()+1), h2(s.size()+1), p1(s.size()+1, 1), p2(s.size()+1, 1) {
        for(size_t i=0;i<s.size();++i) {
            int c=(unsigned char)s[i]+1;
            h1[i+1]=(h1[i]*B+c)%M1;
            h2[i+1]=(h2[i]*B+c)%M2;
            p1[i+1]=p1[i]*B%M1;
            p2[i+1]=p2[i]*B%M2;
        }
    }
    pair<ll, ll> get(int l, int r) {
        return {(h1[r]-h1[l]*p1[r-l]%M1+M1)%M1, (h2[r]-h2[l]*p2[r-l]%M2+M2)%M2};
    }
};
int main() {
    Hash h("abcabc");
    assert(h.get(0, 3)==h.get(3, 6));
    assert(h.get(0, 2)!=h.get(1, 3));
    cout << "OK\n";
}
