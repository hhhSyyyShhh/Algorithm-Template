# STL 接口与语法详解（C++17）

STL 通常指容器、迭代器、算法与函数对象等泛型组件。string、智能指针等也常一起学习，但“标准库”比严格意义上的 STL 更广。接口不只要记名字，还要看**参数、返回值、复杂度、适用条件**。

## 一、先学会读接口【必会】

`a.push_back(3)`：a 是对象，点后面是成员函数名，3 是实参。`std::sort(a.begin(),a.end())`：sort 是命名空间中的通用算法，接收迭代器范围。

```cpp
std::vector<int> a{3, 1, 2};
a.push_back(4);
std::sort(a.begin(), a.end()); // a 为 1,2,3,4
```

### 迭代器与左闭右开区间

`begin()` 指向首元素；`end()` 是最后元素之后的位置，不能解引用。`*it` 访问元素，`++it` 前进。vector 迭代器支持 `it+k` 和差值；set/map 迭代器不支持随机跳转或直接相减。

```cpp
for (auto it = a.begin(); it != a.end(); ++it) {
    std::cout << *it << ' ';
}
```

`[first,last)` 包含 first，不包含 last。排序原数组下标 1 到 3，写 `sort(a.begin()+1,a.begin()+4)`，前提是长度至少 4。

## 二、容器选择速查【必会】

| 容器 | 用途 | 核心代价 |
|---|---|---|
| vector | 动态数组、邻接表 | 下标 O(1)，尾插均摊 O(1)，中间增删 O(n) |
| array | 固定长度数组 | 下标 O(1)，长度编译期确定 |
| deque | 两端增删 | 两端增删 O(1)，下标 O(1) |
| list | 双向链表 | 已知迭代器时插入删除 O(1)，找位置 O(n) |
| stack | 后进先出 | push/pop/top O(1)，取决于底层容器 |
| queue | 先进先出 | push/pop/front O(1)，默认底层 deque |
| priority_queue | 动态取最优元素 | top O(1)，push/pop O(log n) |
| set / map | 有序集合 / 键值映射 | 查询增删通常 O(log n) |
| multiset / multimap | 保留重复键 | 与有序关联容器类似 |
| unordered_set / unordered_map | 哈希集合 / 映射 | 查询增删平均 O(1)，最坏 O(n) |

## 三、vector 与 array【必会】

需要 `<vector>`、`<array>`。初始化含义必须分清：

```cpp
std::vector<int> a(3, 7); // 3 个 7
std::vector<int> b{3, 7}; // 两个元素：3 和 7
std::vector<std::vector<int>> g(5); // 5 个空的邻接表
```

| 接口 | 返回/作用 | 注意 |
|---|---|---|
| `a.size()` | 当前元素个数，size_type | 通常是无符号类型 |
| `a.empty()` | 是否为空，bool | 判空后才能 front/back/pop_back |
| `a[i]` | 元素引用 | 不做标准要求的边界检查；越界是未定义行为 |
| `a.at(i)` | 元素引用 | 越界抛出 out_of_range |
| `a.front()` / `back()` | 首/尾元素引用 | 非空才可用 |
| `a.push_back(x)` | 尾部添加，返回 void | 均摊 O(1)，扩容单次 O(n) |
| `a.emplace_back(args...)` | 在尾部构造对象 | C++17 返回新元素引用；不保证总比 push_back 快 |
| `a.pop_back()` | 删除尾元素，返回 void | 需要返回值时先 back 再 pop |
| `a.insert(it,x)` | 插入，返回新元素迭代器 | 找到位置后仍可能移动大量元素 |
| `a.erase(it)` | 删除，返回后继迭代器 | 删除最后元素时返回 end |
| `a.erase(first,last)` | 删除半开范围，返回后继 | 端点要合法 |
| `a.clear()` | 清空元素 | size 变 0，不保证归还容量 |
| `a.resize(n)` | 改元素个数 | 增加 int 元素默认补 0；缩小时删除尾部 |
| `a.assign(n,x)` | 替换为 n 个 x | 不是在原尾部追加 |
| `a.reserve(n)` | 预留容量 | 不改变 size，不能随后直接访问新下标 |
| `a.capacity()` | 当前可容纳元素数 | 容量与有效元素数不同 |
| `a.data()` | 连续元素存储的指针 | 空数组不能解引用 |

`array<int,3> a{};` 包含 3 个 0，支持 size/fill/at/begin/end，但没有 push_back/resize。

### 迭代器失效：修改容器后还能用旧地址吗

vector 扩容时，原迭代器、指针和引用都会失效；未扩容的尾插仍会使旧 end 失效。erase 使删除位置及其后的引用/迭代器失效。即使提前 reserve，也不能忽视中间插入和删除的影响。

```cpp
for (auto it = a.begin(); it != a.end(); ) {
    if (*it < 0) it = a.erase(it); // 用返回的新迭代器继续
    else ++it;
}
```

上面的 vector 多次删除最坏 O(n²)，批量过滤通常用 erase-remove 惯用法。

## 四、string【必会】

需要 `<string>`；std::string 以 char 单元存储，UTF-8 汉字通常占多个字节，不可把 size 当作汉字个数。

| 接口 | 示例与结果 | 易错点 |
|---|---|---|
| `s.size()` / `length()` | `"abc"` 为 3 | 字节单元数量 |
| `s[i]` / `s.at(i)` | 按位置读写 | 对内容索引只使用 0<=i<size |
| `s += "ab"` / `append` | 追加内容 | `+` 可产生新字符串 |
| `push_back(ch)` / `pop_back()` | 增删尾字符 | pop 前判空 |
| `s.substr(pos,len)` | 当 `s="abcd"` 时，`s.substr(1,2)` 得 `"bc"` | 第二参数是长度，不是结束下标；pos>size 会抛异常 |
| `s.find(pattern)` | 首次匹配位置 | 找不到是 string::npos，不要直接访问 |
| `s.rfind(pattern)` | 从后查找 | 同样检查 npos |
| `s.insert(pos,text)` | 在位置前插入 | 可能线性移动 |
| `s.erase(pos,len)` | 删除从 pos 起最多 len 个字符 | 第二参数仍是长度 |
| `s.replace(pos,len,text)` | 替换一段 | 不同于逐字符替换算法 |
| `s.c_str()` | 以空字符结尾的只读指针 | 容器修改/销毁后不要继续持有旧指针 |

`std::string s="abcd"; auto part=s.substr(1,2);` 得到 bc。`auto pos=s.find("x"); if(pos!=std::string::npos){...}` 是正确查找形状。

## 五、pair、tuple 与结构化绑定【常用】

`<utility>` 提供 pair，`<tuple>` 提供 tuple。

```cpp
std::pair<int,int> p{2, 5}; // p.first=2，p.second=5
std::tuple<int,int,int> t{1, 2, 3};
auto [x, y] = p;
int z = std::get<2>(t); // 索引编译期确定，z=3
```

pair 的默认比较按字典序：先 first，再 second。`tie(a,b)=p` 可赋给已有变量；`auto [a,b]=p` 声明新名字。`make_pair`、`make_tuple` 可以推导元素类型。

## 六、stack、queue 与 deque【必会】

| 类型与头文件 | 常用接口 | 使用条件 |
|---|---|---|
| `stack<T>`，`<stack>` | push、emplace、top、pop、size、empty | LIFO；top/pop 前非空 |
| `queue<T>`，`<queue>` | push、emplace、front、back、pop、size、empty | FIFO；front/back/pop 前非空 |
| `deque<T>`，`<deque>` | push_front/back、pop_front/back、front/back、[] | 两端操作，支持下标 |

stack/queue 是容器适配器，没有普通的 begin/end 遍历接口。`pop()` 只删除、不返回值：先 `int u=q.front();` 再 `q.pop();`。BFS 常用 queue，单调队列需要 deque。

## 七、priority_queue 与比较器【必会】

需要 `<queue>`；greater 来自 `<functional>`。

```cpp
std::priority_queue<int> largest; // 默认大根堆，top 最大
std::priority_queue<int, std::vector<int>, std::greater<int>> smallest;
smallest.push(7);
smallest.push(2); // smallest.top() 为 2
```

接口 push/emplace/pop/top/size/empty；无任意下标访问，也不直接支持原地减少某个键。Dijkstra 用“重复入堆+跳过过期项”，而不是随意修改堆中元素。

比较器的语义要分场景：sort 的 `comp(a,b)==true` 表示 a 排在 b 前；priority_queue 使用 less 时 top 是最大值。不要把“比较器返回 true”一律理解成“a 优先出堆”。

## 八、set、multiset【常用】

需要 `<set>`。set 元素唯一且有序；multiset 允许重复。元素作为排序键，不能通过迭代器直接改值。

| 接口 | 返回/作用 | 注意 |
|---|---|---|
| `s.insert(x)` | set 返回 pair<iterator,bool> | bool 表示本次是否新插入；multiset 返回 iterator |
| `s.find(x)` | 指向 x 的迭代器 | 不存在返回 end |
| `s.count(x)` | 出现个数 | set 为 0/1；multiset 最坏还要计数所有匹配项 |
| `s.erase(x)` | 删除所有等于 x 的元素，返回个数 | multiset 可能一次删多个 |
| `s.erase(it)` | 删除该迭代器位置，返回后继 | it 不能是 end |
| `s.lower_bound(x)` | 首个 >=x | O(log n)，检查 end |
| `s.upper_bound(x)` | 首个 >x | O(log n)，检查 end |

只删 multiset 中一个 x：先 `auto it=s.find(x); if(it!=s.end())s.erase(it);`。set 的成员 lower_bound 通常优于通用 `std::lower_bound(s.begin(),s.end(),x)`，后者的迭代器移动可能达 O(n)。

## 九、map、unordered_map【常用】

需要 `<map>`、`<unordered_map>`。map 按键有序；unordered_map 不保证遍历顺序。

```cpp
std::map<std::string,int> freq;
++freq["apple"]; // key 不存在时先插入默认 int 值 0，再递增
for (const auto& [key, value] : freq) {
    std::cout << key << ':' << value << '\n';
}
```

| 接口 | 含义 |
|---|---|
| `m[key]` | 返回值的引用；键不存在会插入默认值 |
| `m.at(key)` | 不插入；不存在抛 out_of_range |
| `m.find(key)` | 返回 iterator；检查是否 end |
| `m.count(key)` | map/unordered_map 返回 0 或 1 |
| `m.insert({key,value})` | 键已存在时通常保留旧值 |
| `m.emplace(key,value)` | 原位构造式插入；键存在时不覆盖旧值 |
| `m.try_emplace(key,args...)` | C++17，缺键时构造值 |
| `m.insert_or_assign(key,value)` | C++17，存在就赋值，不存在就插入 |
| `m.erase(key)` | 删除并返回删除个数 |

只判断存在性时优先 find/count；不能使用 C++20 才引入的 contains 当作 C++17 接口。unordered_map 的 reserve 可预留桶容量以减少 rehash；rehash 会使迭代器失效，遍历中插入要谨慎。哈希操作的“平均 O(1)”不等于最坏保证。

map/set 插入不会使已有元素迭代器失效；erase 使被删除元素的迭代器失效，其他元素仍可用。具体容器要分别看规则，不能套用 vector 的规则。

## 十、通用算法接口【必会】

需要 `<algorithm>`；下表的 n 是处理范围长度。

| 接口 | 结果与用途 | 条件/时间 |
|---|---|---|
| `sort(first,last)` | 原地升序，返回 void | 随机访问迭代器，O(n log n) |
| `stable_sort` | 等价元素保留原相对顺序 | 内存足够时 O(n log n)，否则比较次数可达 O(n log²n) |
| `reverse(first,last)` | 原地反转，返回 void | O(n) |
| `lower_bound(first,last,x)` | 首个 >=x 的迭代器 | 常用升序范围；随机访问下 O(log n) |
| `upper_bound(first,last,x)` | 首个 >x 的迭代器 | 同上 |
| `binary_search(first,last,x)` | 是否存在，bool | 同一排序关系下有序 |
| `min_element` / `max_element` | 最小/最大元素迭代器 | O(n)；空范围返回 last |
| `find(first,last,x)` | 第一个等于 x 的迭代器 | O(n)，不要求有序 |
| `count(first,last,x)` | 等于 x 的个数 | O(n) |
| `count_if(first,last,pred)` | 满足谓词的个数 | O(n) |
| `any_of` / `all_of` / `none_of` | 是否任意/全部/无元素满足 | O(n)，空范围分别 false/true/true |
| `fill(first,last,x)` | 逐元素赋值 x | O(n)，返回 void |
| `copy(first,last,out)` | 复制到目标起点 | 目标空间须足够；可用 back_inserter 追加 |
| `unique(first,last)` | 相邻去重，返回逻辑新结尾 | O(n)，不自动缩短容器 |
| `remove` / `remove_if` | 移动保留元素，返回逻辑新结尾 | O(n)，不自动 erase |
| `next_permutation` | 改成下一个字典序排列，返回 bool | O(n)，不存在下一排列时回到最小排列 |
| `nth_element(first,nth,last)` | nth 放到排序后应在的位置，两侧分区 | 平均 O(n)，两侧不保证有序；示例 nth 取范围内位置 |

### 排序比较器

```cpp
std::sort(a.begin(), a.end(), [](int x, int y) { return x > y; });
```

这里是降序。比较器需要严格弱序，对任意 x 必须 `comp(x,x)==false`；禁止用 `>=`。结构体按多个字段比较时，第一字段不同时先比较第一字段，相同时再比较第二字段。

### 查找与去重

```cpp
std::sort(a.begin(), a.end());
a.erase(std::unique(a.begin(), a.end()), a.end());
auto it = std::lower_bound(a.begin(), a.end(), 5);
if (it != a.end()) {
    int index = static_cast<int>(it - a.begin());
    // *it 是首个 >=5 的元素，不一定等于 5
}
```

若需要判断精确存在，额外检查 `*it==5`。二分的比较关系必须与排序一致。`unique` 不排序；先排序是为了让所有相等元素相邻，若必须保留原顺序，应另选去重策略。

### 批量删除与追加复制

```cpp
a.erase(std::remove_if(a.begin(), a.end(), [](int x){ return x < 0; }), a.end());
std::vector<int> out;
std::copy(a.begin(), a.end(), std::back_inserter(out)); // <iterator>
```

不能对空 out 直接 `copy(...,out.begin())` 写入不存在的元素。

## 十一、numeric、bitset 与 function【常用】

| 头文件 | 接口 | 说明 |
|---|---|---|
| `<numeric>` | `accumulate(first,last,0LL)` | 累加；初值决定累积类型，用 0LL 避免 int 累积溢出 |
| `<numeric>` | `iota(first,last,start)` | 依次赋 start、start+1…；常用于并查集初始化 |
| `<numeric>` | `partial_sum` | 计算前缀和写入有效目标范围，留意累积类型 |
| `<numeric>` | `gcd(a,b)` / `lcm(a,b)` | C++17；lcm 中间/结果须能表示；绝对值也须可表示 |
| `<bitset>` | `bitset<N>` 的 set/reset/flip/test/count/any/none/all | 固定位数的位集合，N 编译期确定；位 0 是低位 |
| `<functional>` | `function<R(Args...)>` | 保存可调用对象；有类型擦除开销 |
| `<functional>` | `greater<T>` / `less<T>` | 标准比较函数对象 |
| `<iterator>` | `distance` / `advance` / `next` / `prev` | 是否 O(1) 取决于迭代器类型，链式/树式常为线性 |

### 读模板时按这四步查接口

1. 查它是容器成员还是通用算法。
2. 看返回值是元素、引用、迭代器、数量还是 void。
3. 检查非空、有序、目标空间等前提。
4. 检查复杂度和修改后的迭代器是否仍有效。

参考：[vector 接口说明](https://learn.microsoft.com/en-us/cpp/standard-library/vector-class)、[标准库容器](https://learn.microsoft.com/en-us/cpp/standard-library/stl-containers)、[算法](https://learn.microsoft.com/en-us/cpp/standard-library/algorithms)。
