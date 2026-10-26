/*
试除与埃氏筛
用途：单次判断质数，批量筛出上界内所有质数
思路：试除只需到平方根；筛法从每个质数的平方起标记倍数。
复杂度：试除 O(√n)，筛法 O(n log log n)，筛空间 O(n)
注意：0、1 不是质数；试除用 d<=n/d 避免平方溢出；筛法适合可分配内存的上界。
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
bool is_prime(ll n) {
    if(n<2)return false;
    for(ll d=2;d<=n/d;++d)if(n%d==0)return false;
    return true;
}
vector<int> sieve(int n) {
    assert(n>=0);
    vector<bool>prime(n+1, true);
    prime[0]=false;
    if(n>=1)prime[1]=false;
    for(int i=2;i<=n/i;++i)if(prime[i])for(ll j=1LL*i*i;j<=n;j+=i)prime[j]=false;
    vector<int>ans;
    for(int i=2;i<=n;++i)if(prime[i])ans.push_back(i);
    return ans;
}
int main() {
    assert(!is_prime(1) && is_prime(97));
    assert(sieve(10)==vector<int>({2, 3, 5, 7}));
    cout << "OK\n";
}
