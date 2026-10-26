/*
扩展欧几里得与逆元
用途：求 ax+by=gcd(a,b)，计算一般模数下逆元
思路：递归求下一层系数，再反推 x=y1，y=x1-(a/b)*y1；互质时 x 即逆元。
复杂度：时间 O(log mod)，递归空间 O(log mod)
注意：a>=0、mod>1；不互质时逆元不存在；输入及系数中间运算必须在 long long 范围内。
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
ll exgcd(ll a, ll b, ll&x, ll&y) {
    if(!b) {
        x=1;
        y=0;
        return a;
    }
    ll x1, y1;
    ll g=exgcd(b, a%b, x1, y1);
    x=y1;
    y=x1-(a/b)*y1;
    return g;
}
ll inverse(ll a, ll mod) {
    assert(a>=0 && mod>1);
    ll x, y;
    if(exgcd(a, mod, x, y)!=1)return -1;
    return (x%mod+mod)%mod;
}
int main() {
    assert(inverse(3, 11)==4);
    assert(inverse(2, 6)==-1);
    cout << "OK\n";
}
