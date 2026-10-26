// 对应基础语法、函数引用指针与 Lambda。每个例子都解释状态如何变化。
#include <algorithm>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

// 显式检查，不依赖 assert，因此关闭断言时也会运行。
void check(bool ok) {
    if (!ok) throw std::runtime_error("example check failed");
}
void increase(int& x) { ++x; }  // 引用参数修改调用方变量
long long sum(const std::vector<int>& a) {
    long long result = 0;
    for (int x : a) result += x;
    return result;
}
template<class T>
T larger(T a, T b) { return a < b ? b : a; }

int main() {
    int a = 100000, b = 100000;
    check(1LL * a * b == 10000000000LL); // 提前提升乘法类型
    check(7 / 2 == 3);
    int x = 5;
    increase(x);
    int* p = &x;
    *p = 9;
    check(x == 9);
    std::vector<int> values{3, 1, 2};
    for (auto& v : values) ++v; // 原数组变成 4,2,3
    check(sum(values) == 9);
    check(larger<double>(2, 3.5) == 3.5);
    int limit = 10;
    auto value_capture = [limit](int n) { return n < limit; };
    auto reference_capture = [&limit](int n) { return n < limit; };
    limit = 3;
    check(value_capture(5) && !reference_capture(5));
    std::function<int(int)> fib = [&](int n) -> int {
        if (n <= 1) return n;
        return fib(n - 1) + fib(n - 2);
    };
    check(fib(8) == 21); // 仅演示递归语法，不适合大 n
    std::pair<int,int> edge{2, 7};
    auto [u, weight] = edge;
    check(u == 2 && weight == 7);
    std::cout << "语法、引用、模板、Lambda 示例通过\n";
}
