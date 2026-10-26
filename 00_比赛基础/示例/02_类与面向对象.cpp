#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

void check(bool ok) {
    if (!ok) throw std::runtime_error("example check failed");
}
class Counter {
    int value_; // class 默认为 private
public:
    explicit Counter(int initial = 0) : value_(initial) {}
    void add(int delta) { value_ += delta; }
    void reset() { value_ = 0; }
    int value() const { return value_; }
};
struct Shape {
    virtual double area() const = 0;
    virtual ~Shape() = default; // 支持通过基类指针销毁实际的派生对象
};
struct Square : public Shape {
    double side;
    explicit Square(double s) : side(s) {}
    double area() const override { return side * side; }
};
struct Group {
    std::vector<int> members; // 容器自动管理自己的资源
};
int main() {
    Counter c(3);
    c.add(2);
    check(c.value() == 5);
    const Counter& view = c;
    check(view.value() == 5); // const 引用可调用 const 成员函数
    c.reset();
    check(c.value() == 0);
    Group first{{1, 2}};
    Group second = first; // 成员 vector 复制元素
    second.members[0] = 99;
    check(first.members[0] == 1);
    std::unique_ptr<Shape> shape = std::make_unique<Square>(3);
    check(shape->area() == 9); // -> 访问指针指向的对象，触发动态分派
    std::cout << "类、封装、复制、虚函数与资源管理示例通过\n";
}
