/*
KMP匹配
用途：精确查找模式串在文本中所有出现位置
思路：前缀函数 pi[i] 表示前缀结尾最长相同真前后缀长度；失配时跳到 pi[j-1]。
复杂度：时间 O(n+m)，空间 O(m)，另加结果空间
注意：结果为 0 下标；匹配后回退以支持重叠；此实现空模式匹配所有 n+1 个边界。
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
vector<int> kmp(const string&s, const string&p) {
    int m=p.size();
    if(!m) {
        vector<int>a(s.size()+1);
        iota(a.begin(), a.end(), 0);
        return a;
    }
    vector<int>pi(m), ans;
    for(int i=1, j=0;i<m;++i) {
        while(j && p[i]!=p[j])j=pi[j-1];
        if(p[i]==p[j])++j;
        pi[i]=j;
    }
    for(int i=0, j=0;i<(int)s.size();++i) {
        while(j && s[i]!=p[j])j=pi[j-1];
        if(s[i]==p[j])++j;
        if(j==m) {
            ans.push_back(i-m+1);
            j=pi[j-1];
        }
    }
    return ans;
}
int main() {
    assert(kmp("aaaaa", "aaa")==vector<int>({0, 1, 2}));
    assert(kmp("abc", "d").empty());
    cout << "OK\n";
}
