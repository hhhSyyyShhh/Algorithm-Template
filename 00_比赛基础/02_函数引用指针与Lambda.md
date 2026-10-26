# 02 函数、引用、指针与 Lambda

## 一、函数的输入和输出【必会】

```cpp
int add(int a, int b) { return a + b; }
void increase(int& x) { ++x; }
int first(const std::vector<int>& a) { return a.at(0); }
```

`int add` 表示返回 int；括号内是形参；调用时 `add(2,3)` 中的 2、3 是实参。函数重载可以使用同名不同参数列表，但不能只靠返回类型区分。默认参数如 `void dfs(int u,int p=-1)` 可省略末尾实参，重复声明时不要重复给默认值。

| 参数形式 | 是否复制 | 能否修改调用方对象 | 适用 |
|---|---|---|---|
| `int x` | 复制整数 | 否 | 小型值、需要局部副本 |
| `vector<int> a` | 复制整个容器 | 否 | 特意需要独立修改副本 |
| `vector<int>& a` | 不复制容器 | 能 | 排序、原地更新 |
| `const vector<int>& a` | 不复制容器 | 不能通过该引用修改 | 只读传入数组 |
| `int* p` | 复制地址 | 可修改它指向的有效对象 | 允许空值或需要指针语义 |

值传递 `sort_copy(vector<int> a)` 会带来 O(n) 复制成本，可能是有意为之，不能统一改成引用。

## 二、引用与指针【必会】

```cpp
int x = 5;
int& ref = x; // x 的别名，必须初始化
ref = 8;      // x 变成 8
int* p = &x;  // &x 取得 x 的地址
*p = 9;       // *p 访问地址指向的对象，x 变成 9
p = nullptr;  // 空指针，不指向对象
```

`&` 在声明里表示引用，在表达式里表示取地址；`*` 在声明里表示指针，在表达式里可表示解引用或乘法。具体看上下文。

- 引用初始化后不能改为绑定另一个对象；`ref = y` 是赋值给原对象。
- 指针可重新指向别处，可以为空；解引用前必须确保对象有效。
- `const int* p`：不能通过 p 修改整数；`int* const p`：指针本身不能换目标；`const int* const p` 两者都受限。
- 不要返回局部变量的地址或引用；函数结束后对象已销毁，形成悬空引用/指针。
- 不要保留 vector 元素的引用后再 push_back，扩容可能使它失效。

## 三、递归【必会】

```cpp
long long factorial(int n) { // 仅接受 0<=n<=20，避免 long long 溢出
    if (n <= 1) return 1;    // 终止条件
    return n * factorial(n - 1); // 规模变小，并利用子问题结果
}
```

调用 `factorial(3)` 会先进入 2，再进入 1；返回时从 1 开始逐层相乘。每一层都有自己的局部变量和返回位置。检查三件事：何时结束、参数是否走向结束、返回值如何组合。时间 O(n)，额外栈空间 O(n)。

DFS 的递归深度可能是节点数。换成显式 stack 可以把递归状态搬到堆上管理；若要模拟后序，需要记录“节点处理到哪一步”。

## 四、Lambda：就地定义一个函数对象【常用】

基本形状是 `[捕获](参数) -> 返回类型 { 函数体 };`。返回类型常可省略。

```cpp
int limit = 10;
auto by_value = [limit](int x) { return x < limit; };
auto by_ref = [&limit](int x) { return x < limit; };
limit = 3;
// by_value(5) 为 true；by_ref(5) 为 false
```

| 捕获 | 含义 | 注意 |
|---|---|---|
| `[]` | 不捕获外部局部变量 | 适合无外部状态的比较器 |
| `[x]` | 捕获 x 的副本 | 看到的是创建时的值 |
| `[&x]` | 引用捕获 x | 看到外部后续修改；x 必须仍然活着 |
| `[=]` | 隐式按值捕获用到的外部局部变量 | 不等于深拷贝所有被指针指向的对象 |
| `[&]` | 隐式引用捕获用到的外部局部变量 | 返回/异步保存时留意悬空 |
| `[x, &y]` | 分别指定 | 有利于明确依赖 |

值捕获默认不能修改捕获副本；加 `mutable` 可修改副本，仍不直接修改外部原值。不要为了省打字到处写 `[&]`，先明确需要捕获什么。

递归 Lambda 在 C++17 可这样写：

```cpp
std::function<int(int)> fib = [&](int n) -> int {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}; // <functional>；朴素 Fibonacci 时间是指数级，仅作语法演示
```

也可显式传入自身：`auto dfs = [&](auto&& self, int u) -> void { /* self(self,v); */ };`，用 `dfs(dfs,0)` 启动。该写法省去 std::function 的类型擦除开销，但初学阶段优先读清楚参数。

## 五、模板、auto 与结构化绑定【常用】

```cpp
template<class T>
T larger(T a, T b) { return a < b ? b : a; }

std::pair<int,int> edge{2, 7};
auto [u, v] = edge;    // C++17：复制拆成两个名字
const auto& [x, y] = edge; // 引用只读
```

`larger(2,3)` 会推导 T=int；`larger(2,3.5)` 无法从两个不同类型直接推导同一个 T，可明确 `larger<double>(2,3.5)`。`auto` 变量通常在初始化时推导类型；范围循环 `for (auto [v,w] : g[u])` 复制 pair，需要修改原边时用 `auto& [v,w]`。

**自测**：把一个传值排序函数改成原地排序；解释引用捕获为何可能悬空；手算三层递归的进入与返回顺序。
