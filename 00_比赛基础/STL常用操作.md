# STL 常用操作

| 容器/算法 | 核心操作 | 注意 |
|---|---|---|
| vector | push_back、pop_back、size | 下标访问先保证不越界；扩容可能使引用失效 |
| string | substr(pos,len)、find | find 找不到返回 string::npos |
| stack | push、top、pop | 后进先出；访问前判空 |
| queue | push、front、pop | 先进先出；访问前判空 |
| deque | push_back、pop_back、pop_front | 单调队列常用 |
| priority_queue | push、top、pop | 默认大根堆；小根堆加 greater<T> |
| set/map | insert、find、erase | 通常 O(log n)；map[key] 会插入不存在的键 |
| unordered_map | find、operator[] | 平均 O(1)，最坏 O(n)，竞赛中注意哈希退化 |
| sort | sort(a.begin(),a.end()) | 排序 O(n log n)，比较器必须严格 |
| lower_bound | 第一个 >=x 的迭代器 | 范围先有序；返回 end 时不能解引用 |
| upper_bound | 第一个 >x 的迭代器 | 同上 |
| unique | unique 后接 erase | 只去掉相邻重复；通常先排序 |
| reverse | reverse(begin,end) | 原地反转 |
| gcd/lcm | std::gcd、std::lcm | C++17，lcm 注意溢出 |

默认迭代器区间都是左闭右开 [begin,end)。不要混淆 size() 的无符号类型和可能为负的下标。
