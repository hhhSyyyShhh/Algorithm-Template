/*
字典树
用途：保存单词，查询精确单词出现次数和前缀数量
思路：每条边代表一个字母；共享前缀复用节点；终点计数区分完整单词。
复杂度：插入查询 O(L)，空间 O(26*总字符数)
注意：只接受小写 a-z；重复插入会累计；空串计数也支持；插入时不要持有 vector 元素引用后扩容。
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
struct Trie {
    struct Node {
        array<int, 26>next{};
        int end=0, pass=0;
    };
    vector<Node>t{Node{}};
    void insert(const string&s) {
        int u=0;
        ++t[u].pass;
        for(char ch:s) {
            int c=ch-'a';
            assert(c>=0 && c<26);
            if(!t[u].next[c]) {
                int id=t.size();
                t[u].next[c]=id;
                t.push_back(Node{});
            }
            u=t[u].next[c];
            ++t[u].pass;
        }
        ++t[u].end;
    }
    int node(const string&s)const{int u=0;
    for(char ch:s) {
        int c=ch-'a';
        assert(c>=0 && c<26);
        u=t[u].next[c];
        if(!u)return -1;
    }
    return u;
    }
    int count(const string&s)const{int u=node(s);
    return u<0?0:t[u].end;
    }
    int prefix_count(const string&s)const{int u=node(s);
    return u<0?0:t[u].pass;
    }
};
int main() {
    Trie t;
    t.insert("abc");
    t.insert("ab");
    t.insert("ab");
    assert(t.count("ab")==2);
    assert(t.prefix_count("a")==3);
    assert(t.count("a")==0);
    cout << "OK\n";
}
