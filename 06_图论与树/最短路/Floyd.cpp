/*
Floyd
用途：小规模图的全源最短路
思路：按允许经过的中间点 k 逐步扩展，d[i][j]=min(d[i][j],d[i][k]+d[k][j])。
复杂度：时间 O(n³)，空间 O(n²)
注意：可有负边但最短路要求无负环；重边取最小；对角设 0；INF 两侧先判断。
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
const ll INF=LLONG_MAX/4;
void floyd(vector<vector<ll>>&d) {
    int n=d.size();
    for(int k=0;k<n;++k)for(int i=0;i<n;++i)for(int j=0;j<n;++j)
    if(d[i][k]!=INF && d[k][j]!=INF)d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
}
int main() {
    vector<vector<ll>>d={{0, 5, 1}, {INF, 0, INF}, {INF, 2, 0}};
    floyd(d);
    assert(d[0][1]==3);
    cout << "OK\n";
}
