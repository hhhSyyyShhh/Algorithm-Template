/*
二维前缀和
用途：静态矩阵的子矩形求和
思路：容斥：当前值 + 上方和 + 左方和 - 重叠和。查询时同样容斥。
复杂度：预处理 O(nm)，查询 O(1)，空间 O(nm)
注意：矩阵非空且各行等长；数组 0 下标，查询四个坐标均包含端点。
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
vector<vector<ll>> prefix2(const vector<vector<int>>& a) {
    int n=a.size(), m=a[0].size();
    vector<vector<ll>> s(n+1, vector<ll>(m+1));
    for(int i=0;i<n;++i) for(int j=0;j<m;++j)
    s[i+1][j+1]=a[i][j]+s[i][j+1]+s[i+1][j]-s[i][j];
    return s;
}
ll rectangle(const vector<vector<ll>>& s, int x1, int y1, int x2, int y2) {
    return s[x2+1][y2+1]-s[x1][y2+1]-s[x2+1][y1]+s[x1][y1];
}
int main() {
    auto s=prefix2({{1, 2, 3}, {4, 5, 6}});
    assert(rectangle(s, 0, 1, 1, 2)==16);
    cout << "OK\n";
}
