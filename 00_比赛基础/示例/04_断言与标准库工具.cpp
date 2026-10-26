// 分别在默认与 -DNDEBUG 下运行，观察断言表达式是否被执行。
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

void check(bool ok) {
    if (!ok) throw std::runtime_error("example check failed");
}
static_assert(sizeof(long long) >= 8, "need at least 8 bytes");
int main() {
    int count = 0;
    ++count; // 必要状态修改必须放在断言外面
    assert(count == 1);
    check(count == 1);
    assert((std::pair<int,int>{1,2} == std::make_pair(1,2)));

    int evaluated = 0;
    // 故意演示断言的求值差异，不作为业务逻辑依赖。
    auto observe = [&evaluated]() { ++evaluated; return true; };
    (void)observe; // -DNDEBUG 下宏不求值，也不产生 unused 警告
    assert(observe());
#ifdef NDEBUG
    check(evaluated == 0);
    std::cout << "NDEBUG: 断言表达式未执行\n";
#else
    check(evaluated == 1);
    std::cout << "断言开启: 表达式执行一次\n";
#endif
    std::vector<int> v{1,2};
    bool caught = false;
    try { (void)v.at(100); }
    catch (const std::out_of_range&) { caught = true; }
    check(caught); // 断言关闭不影响 at 的越界检查
    std::size_t pos = 0;
    int number = std::stoi("12x", &pos);
    check(number == 12 && pos == 2);
    check(std::to_string(number) == "12");
    char ch = '7';
    check(std::isdigit(static_cast<unsigned char>(ch)) != 0);
    check(std::floor(-1.2) == -2 && std::ceil(-1.2) == -1);
    check(std::round(-1.5) == -2);
    check(std::clamp(12, 0, 10) == 10);
    check(std::numeric_limits<double>::lowest() < 0);
    std::fill(v.begin(), v.end(), 1);
    check(v[0] == 1 && v[1] == 1);
    std::cout << "断言、异常与标准库工具示例通过\n";
}
