# C++17 前置知识：学习入口

目标是让你读懂、修改并独立写出这个仓库里的算法代码。默认 C++17，兼顾 ACM 竞赛与一般 C++ 编程。这里覆盖常用知识，不宣称穷尽全部标准库接口。

## 按什么顺序学

| 顺序 | 资料 | 要达到的程度 |
|---|---|---|
| 1 | [基础语法](01_C++基础语法.md) | 看懂类型、表达式、循环、数组和输入输出 |
| 2 | [函数、引用、指针与 Lambda](02_函数引用指针与Lambda.md) | 看懂参数如何传递、递归怎样返回、捕获怎样工作 |
| 3 | [类与面向对象](03_类与面向对象.md) | 看懂 struct/class、构造函数、成员函数、封装与多态 |
| 4 | [STL 接口与语法](STL常用操作.md) | 能选择容器、查接口、正确遍历和修改 |
| 5 | [断言与标准库工具](04_断言与常用标准库工具.md) | 分清 assert、static_assert、异常和普通检查 |
| 6 | [读模板与排错](05_读模板与排错.md) | 能解释现有模板中的 C++ 写法并排查常见错误 |

标签说明：**必会**是读算法模板需要的基础；**常用**是经常查阅的接口；**了解**可以在遇到时回看。

## 先学什么，不用急着学什么

- **第一遍必会**：vector、string、pair、sort、二分接口、引用、const、struct、构造函数、assert。
- **做题时补充**：map/set、优先队列、迭代器失效、Lambda、递归 Lambda、模板函数。
- **逐步了解**：继承、虚函数、智能指针、移动语义、异常。普通算法题通常不用设计完整继承体系。

每次练习：看用途 → 手算例子 → 编译运行 → 改一处输入 → 解释结果 → 遮住代码重写。

## 可直接运行的配套示例

[示例目录](示例/)中每个 cpp 都有自己的 main；一次编译一个，不要一起链接。

```bash
cd ~/Desktop/Algorithm-Template
mkdir -p build
clang++ -std=c++17 -Wall -Wextra -pedantic "00_比赛基础/示例/01_语法与函数.cpp" -o build/basic
./build/basic
```

文档里的短代码块是**局部示例**：需要补齐头文件和 main；完整可运行版本见示例目录。

## 查阅资料

按 C++17 语义编写，阅读在线文档时留意 C++20/23/26 新接口。Microsoft 文档中的 Windows 专属接口不纳入本套通用写法。

- [Microsoft C++ 标准库概览](https://learn.microsoft.com/en-us/cpp/standard-library/cpp-standard-library-overview)
- [Microsoft C++ 语言参考](https://learn.microsoft.com/en-us/cpp/cpp/cpp-language-reference)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
