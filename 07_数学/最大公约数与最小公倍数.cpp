/*
最大公约数与最小公倍数
用途：整除相关的基础运算
思路：欧几里得算法不断把 (a,b) 换成 (b,a%b)；lcm=a/gcd*b。
复杂度：时间 O(log min(a,b))，空间 O(1)
注意：这里要求非负整数；lcm 结果必须能放入 long long；先除后乘降低中间溢出风险。
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
ll gcd_manual(ll a, ll b) {
    while(b) {
        ll r=a%b;
        a=b;
        b=r;
    }
    return a;
}
ll lcm_manual(ll a, ll b) {
    if(a==0 || b==0)return 0;
    return a/gcd_manual(a, b)*b;
}
int main() {
    assert(gcd_manual(18, 24)==6);
    assert(lcm_manual(18, 24)==72);
    assert(lcm_manual(0, 5)==0);
    cout << "OK\n";
}
