/*
组合数与卡特兰数
用途：计算组合数 C(n,k) 和卡特兰数
思路：杨辉递推 C(n,k)=C(n-1,k-1)+C(n-1,k)；Catalan 用左右子结构数量乘积求和。
复杂度：预处理时间 O(n²)，空间 O(n²)；Catalan 时间 O(n²)、空间 O(n)
注意：模数固定 10^9+7；此版不需要逆元；Catalan 可计数合法括号、合法栈进出顺序。
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
const ll MOD=1000000007;
vector<vector<ll>> combinations(int n) {
    vector<vector<ll>>c(n+1, vector<ll>(n+1));
    for(int i=0;i<=n;++i) {
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;++j)c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
    }
    return c;
}
ll catalan(int n) {
    vector<ll>c(n+1);
    c[0]=1;
    for(int i=1;i<=n;++i)for(int l=0;l<i;++l)c[i]=(c[i]+c[l]*c[i-1-l])%MOD;
    return c[n];
}
int main() {
    assert(combinations(5)[5][2]==10);
    assert(catalan(5)==42);
    assert(catalan(0)==1);
    cout << "OK\n";
}
