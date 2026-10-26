/*
二进制与子集枚举
用途：检查某一位、统计 1、枚举所有子集
思路：第 k 位对应 2^k；x&(x-1) 每次清掉最低的 1；掩码表示集合。
复杂度：统计 O(1 的个数)，枚举 O(2^n)，额外空间 O(1)
注意：使用无符号数；位编号从 0 开始；示例 n<31，实际枚举规模通常远小于 31。
学习方式：先读说明，再手算 main 中的例子，最后遮住实现自己重写。
*/
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
int popcount_manual(unsigned x) {
    int c=0;
    while(x) {
        x&=x-1;
        ++c;
    }
    return c;
}
bool has_bit(unsigned x, int k) {
    return (x>>k)&1u;
}
int subsets(int n) {
    assert(0<=n && n<31);
    int count=0;
    for(unsigned mask=0;mask<(1u<<n);++mask) {
        ++count;
/* mask 的第 i 位代表选不选 i */
    }
    return count;
}
int main() {
    assert(popcount_manual(13)==3);
    assert(has_bit(13, 2));
    assert(subsets(3)==8);
    cout << "OK\n";
}
