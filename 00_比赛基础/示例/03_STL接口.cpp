#include <algorithm>
#include <array>
#include <bitset>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

void check(bool ok) {
    if (!ok) throw std::runtime_error("example check failed");
}
int main() {
    std::vector<int> a(3, 7), b{3, 7};
    check(a.size() == 3 && b.size() == 2);
    b.reserve(100);
    check(b.size() == 2 && b.capacity() >= 100); // reserve 不创造元素
    b.resize(4);
    check(b[2] == 0);
    std::vector<int> v{3, -1, 2, 2, 5};
    v.erase(std::remove_if(v.begin(), v.end(), [](int x){ return x < 0; }), v.end());
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    check(v == std::vector<int>({2, 3, 5}));
    auto it = std::lower_bound(v.begin(), v.end(), 4);
    check(it != v.end() && *it == 5);
    check(std::lower_bound(v.begin(), v.end(), 10) == v.end());
    check(std::accumulate(v.begin(), v.end(), 0LL) == 10);
    std::vector<int> out;
    std::copy(v.begin(), v.end(), std::back_inserter(out));
    check(out == v);
    std::iota(out.begin(), out.end(), 8);
    check(out == std::vector<int>({8, 9, 10}));
    std::string s = "abcd";
    check(s.substr(1, 2) == "bc" && s.find("x") == std::string::npos);
    std::stack<int> st;
    st.push(1); st.push(2);
    int top = st.top(); st.pop();
    check(top == 2 && st.top() == 1);
    std::queue<int> q;
    q.push(1); q.push(2); q.pop();
    check(q.front() == 2);
    std::deque<int> dq;
    dq.push_front(2); dq.push_back(3);
    check(dq.front() == 2 && dq.back() == 3);
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    pq.push(7); pq.push(2);
    check(pq.top() == 2);
    std::multiset<int> ms{2, 2, 3};
    auto found = ms.find(2);
    if (found != ms.end()) ms.erase(found); // 只删一个
    check(ms.count(2) == 1);
    std::set<int> unique_values{3, 1, 3};
    check(unique_values.size() == 2 && *unique_values.lower_bound(2) == 3);
    std::map<std::string,int> freq;
    check(freq.find("apple") == freq.end() && freq.empty());
    ++freq["apple"];
    freq.insert_or_assign("apple", 5);
    check(freq.at("apple") == 5 && freq.size() == 1);
    std::unordered_map<int,int> hash;
    hash.reserve(10);
    hash.try_emplace(2, 7);
    hash.try_emplace(2, 9); // 不覆盖原值
    check(hash.at(2) == 7);
    std::array<int,3> fixed{};
    fixed.fill(1);
    check(fixed[2] == 1);
    std::bitset<8> bits(13);
    check(bits.count() == 3 && bits.test(2));
    std::tuple<int,int,int> t{1, 2, 3};
    check(std::get<2>(t) == 3);
    check(std::gcd(18, 24) == 6 && std::lcm(18, 24) == 72);
    std::cout << "STL 接口与边界示例通过\n";
}
