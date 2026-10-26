/*
数组模拟单链表
用途：学习插入删除和链式关系
思路：下标充当地址，next 保存后继；0 是哨兵头结点，-1 表示结束。
复杂度：已知节点时插入删除 O(1)，查找 O(n)，空间 O(操作数)
注意：erase_after 要求后继存在；编号是内部节点编号，并非链表中的第几个位置。
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
struct List {
    vector<int>value{0}, nxt{-1};
    int insert_after(int p, int x) {
        int id=value.size();
        value.push_back(x);
        nxt.push_back(nxt[p]);
        nxt[p]=id;
        return id;
    }
    void erase_after(int p) {
        assert(nxt[p]!=-1);
        nxt[p]=nxt[nxt[p]];
    }
};
int main() {
    List l;
    int a=l.insert_after(0, 2);
    l.insert_after(a, 3);
    l.erase_after(0);
    assert(l.value[l.nxt[0]]==3);
    cout << "OK\n";
}
