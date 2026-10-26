/*
Dijkstra
用途：非负权图单源最短路
思路：小根堆取当前最近点，用它松弛邻边；跳过堆中过期的距离。
复杂度：时间 O((V+E)log(E+2))，空间 O(V+E)
注意：禁止负权；INF 表示不可达；要求有限距离和加法均不会超过 INF。
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
vector<ll> dijkstra(const vector<vector<pair<int, ll>>>&g, int s) {
    vector<ll>d(g.size(), INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>q;
    d[s]=0;
    q.push({0, s});
    while(!q.empty()) {
        auto [du, u]=q.top();
        q.pop();
        if(du!=d[u])continue;
        for(auto [v, w]:g[u]) {
            assert(w>=0);
            if(d[v]>du+w) {
                d[v]=du+w;
                q.push({d[v], v});
            }
        }
    }
    return d;
}
int main() {
    auto d=dijkstra({{{1, 5}, {2, 1}}, {}, {{1, 2}}, {}}, 0);
    assert(d[1]==3 && d[3]==INF);
    cout << "OK\n";
}
