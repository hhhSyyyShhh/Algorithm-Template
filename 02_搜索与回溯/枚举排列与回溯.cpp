/*
枚举排列与回溯
用途：枚举 0 到 n-1 的所有排列
思路：选择未用元素→递归→撤销选择；路径长度为 n 时收集答案。
复杂度：时间 O(n*n!)，含输出空间 O(n*n!)
注意：重复值排列需要额外去重；n 较大时不要保存所有结果，改为现场处理。
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
vector<vector<int>> permutations(int n) {
    vector<vector<int>>ans;
    vector<int>path, used(n);
    function<void()>go=[&]() {
        if((int)path.size()==n) {
            ans.push_back(path);
            return;
        }
        for(int i=0;i<n;++i)if(!used[i]) {
            used[i]=1;
            path.push_back(i);
            go();
            path.pop_back();
            used[i]=0;
        }
    };
    go();
    return ans;
}
int main() {
    auto p=permutations(3);
    assert(p.size()==6);
    assert(p.front()==vector<int>({0, 1, 2}));
    cout << "OK\n";
}
