/*
排序与自定义比较
用途：升序排序、结构体按多个字段排序
思路：sort 按比较器决定先后；stable_sort 保留等价元素原顺序。
复杂度：sort 时间 O(n log n)，通常栈空间 O(log n)
注意：比较器必须用严格小于关系，不能用 <=；排序会改变原数组。
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
struct Student {
    int score, id;
};
void order(vector<Student>& a) {
    sort(a.begin(), a.end(), [](const Student& x, const Student& y) {
        if(x.score!=y.score)return x.score>y.score;  // 分数降序
        return x.id<y.id;  // 同分编号升序
    });
}
int main() {
    vector<Student>a={{80, 2}, {90, 3}, {80, 1}};
    order(a);
    assert(a[0].id==3 && a[1].id==1);
    cout << "OK\n";
}
