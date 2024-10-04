

# std::initializer_list

1. template< class T >
class initializer_list;

std::initializer_list<T> 类型对象是一个访问 const T 类型对象数组的轻量代理对象。

#### std::initializer_list 对象在这些时候自动构造：
1. 用花括号初始化器列表列表初始化一个对象，其中对应构造函数接受一个 std::initializer_list 参数
2. 以花括号初始化器列表为赋值的右运算数，或函数调用参数，而对应的赋值运算符/函数接受 std::initializer_list 参数
3. 绑定花括号初始化器列表到 auto ，包括在范围 for 循环中

```cpp{.line-numbers}
#include <iostream>
#include <initializer_list>
 
int main() 
{
    std::initializer_list<int> empty_list;
    std::cout << "empty_list.size(): " << empty_list.size() << '\n';
 
    // 用列表初始化创建初始化器列表
    std::initializer_list<int> digits {1, 2, 3, 4, 5};
    std::cout << "digits.size(): " << digits.size() << '\n';
 
    // auto 的特殊规则表示‘ fraction ’拥有类型
    // type std::initializer_list<double>
    auto fractions = {3.14159, 2.71828};
    std::cout << "fractions.size(): " << fractions.size() << '\n';
}
```

```cpp
#include <iostream>
#include <vector>
#include <initializer_list>
 
template <class T>
struct S {
    std::vector<T> v;
    S(std::initializer_list<T> l) : v(l) {
         std::cout << "constructed with a " << l.size() << "-element list\n";
    }
    void append(std::initializer_list<T> l) {
        v.insert(v.end(), l.begin(), l.end());
    }
    std::pair<const T*, std::size_t> c_arr() const {
        return {&v[0], v.size()};  // 在 return 语句中复制列表初始化
                                   // 这不使用 std::initializer_list
    }
};
 
template <typename T>
void templated_fn(T) {}
 
int main()
{
    S<int> s = {1, 2, 3, 4, 5}; // 复制初始化
    s.append({6, 7, 8});      // 函数调用中的列表初始化
 
    std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";
 
    for (auto n : s.v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    std::cout << "Range-for over brace-init-list: \n";
 
    for (int x : {-1, -2, -3}) // auto 的规则令此带范围 for 工作
        std::cout << x << ' ';
    std::cout << '\n';
 
    auto al = {10, 11, 12};   // auto 的特殊规则
 
    std::cout << "The list bound to auto has size() = " << al.size() << '\n';
 
//    templated_fn({1, 2, 3}); // 编译错误！“ {1, 2, 3} ”不是表达式，
                             // 它无类型，故 T 无法推导
    templated_fn<std::initializer_list<int>>({1, 2, 3}); // OK
    templated_fn<std::vector<int>>({1, 2, 3});           // 也 OK
}
```