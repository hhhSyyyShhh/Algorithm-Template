/*
C++竞赛起手式
用途：标准输入输出、常见类型及容器
思路：关闭同步加速 cin/cout；输入前检查读取成功；long long 用于较大整数。
复杂度：示例时间 O(n)，空间 O(1)
注意：提交时按题目改 main；不要把其他模板的示例 main 一起复制；关闭同步后避免混用 scanf/printf。
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
ll read_and_sum(istream& input) {
    int n;
    if(!(input>>n))return 0;
    ll sum=0, x;
    for(int i=0;i<n;++i) {
        input>>x;
        sum+=x;
    }
    return sum;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 使用方式：删掉本 main，改为 cout << read_and_sum(cin) << "\n";
    cout << "OK\n";
}
