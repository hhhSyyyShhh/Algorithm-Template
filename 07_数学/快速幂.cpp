/*
快速幂
用途：计算 a 的 b 次方对 mod 取模
思路：指数二进制逐位处理；当前位为 1 就乘入答案，每轮底数平方、指数右移。
复杂度：时间 O(log b)，空间 O(1)
注意：b>=0，1<=mod<=10^9+7；此范围保证 long long 乘法不溢出；更大模数需防溢出乘法。
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
ll mod_pow(ll a, ll b, ll mod) {
    assert(b>=0 && mod>=1 && mod<=1000000007LL);
    a=(a%mod+mod)%mod;
    ll ans=1%mod;
    while(b) {
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int main() {
    assert(mod_pow(2, 10, 1000)==24);
    assert(mod_pow(2, 0, 1)==0);
    assert(mod_pow(-2, 3, 7)==6);
    cout << "OK\n";
}
