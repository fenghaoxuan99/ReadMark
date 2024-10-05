

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [std::function](#stdfunction)
- [std::bind](#stdbind)
      - [std::is_bind_expression](#stdis_bind_expression)
        - [成员常量](#成员常量)
        - [帮助变量模板](#帮助变量模板)

<!-- /code_chunk_output -->




# std::function
template< class R, class... Args >
class function<R(Args...)>;

类模板 std::function 是通用多态函数封装器。
std::function 的实例能存储、复制及调用任何可调用 (Callable) 目标——函数、 lambda 表达式、 bind 表达式或其他函数对象，还有指向成员函数指针和指向数据成员指针。

```cpp{.line-numbers}
#include <functional>
#include <iostream>
 
struct Foo {
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_+i << '\n'; }
    int num_;
};
 
void print_num(int i)
{
    std::cout << i << '\n';
}
 
struct PrintNum {
    void operator()(int i) const
    {
        std::cout << i << '\n';
    }
};
 
int main()
{
    // 存储自由函数
    std::function<void(int)> f_display = print_num;
    f_display(-9);
 
    // 存储 lambda
    std::function<void()> f_display_42 = []() { print_num(42); };
    f_display_42();
 
    // 存储到 std::bind 调用的结果
    std::function<void()> f_display_31337 = std::bind(print_num, 31337);
    f_display_31337();
 
    // 存储到成员函数的调用
    std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
    const Foo foo(314159);
    f_add_display(foo, 1);
    f_add_display(314159, 1);
 
    // 存储到数据成员访问器的调用
    std::function<int(const Foo &)> f_num = &Foo::num_;
    std::cout << "num_: " << f_num(foo) << '\n';
 
    // 存储到成员函数及对象的调用
    using std::placeholders::_1;
    std::function<void(int)> f_add_display2 = std::bind( &Foo::print_add, foo, _1 );
    f_add_display2(2);
 
    // 存储到成员函数和对象指针的调用
    std::function<void(int)> f_add_display3 = std::bind( &Foo::print_add, &foo, _1 );
    f_add_display3(3);
 
    // 存储到函数对象的调用
    std::function<void(int)> f_display_obj = PrintNum();
    f_display_obj(18);
}
```







# std::bind
1. template< class R, class F, class... Args >
/*unspecified*/ bind( F&& f, Args&&... args );
函数模板 bind 生成 f 的转发调用包装器。调用此包装器等价于以一些绑定到 args 的参数调用 f 。

```cpp
#include <random>
#include <iostream>
#include <memory>
#include <functional>
 
void f(int n1, int n2, int n3, const int& n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}
 
int g(int n1)
{
    return n1;
}
 
struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1+n2 << '\n';
    }
    int data = 10;
};
 
int main()
{
    using namespace std::placeholders;  // 对于 _1, _2, _3...
 
    // 演示参数重排序和按引用传递
    int n = 7;
    // （ _1 与 _2 来自 std::placeholders ，并表示将来会传递给 f1 的参数）
    auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);
    n = 10;
    f1(1, 2, 1001); // 1 为 _1 所绑定， 2 为 _2 所绑定，不使用 1001
                    // 进行到 f(2, 42, 1, n, 7) 的调用
 
    // 嵌套 bind 子表达式共享占位符
    auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
    f2(10, 11, 12); // 进行到 f(12, g(12), 12, 4, 5); 的调用
 
    // 常见使用情况：以分布绑定 RNG
    std::default_random_engine e;
    std::uniform_int_distribution<> d(0, 10);
    std::function<int()> rnd = std::bind(d, e); // e 的一个副本存储于 rnd
    for(int n=0; n<10; ++n)
        std::cout << rnd() << ' ';
    std::cout << '\n';
 
    // 绑定指向成员函数指针
    Foo foo;
    auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
    f3(5);
 
    // 绑定指向数据成员指针
    auto f4 = std::bind(&Foo::data, _1);
    std::cout << f4(foo) << '\n';
 
    // 智能指针亦能用于调用被引用对象的成员
    std::cout << f4(std::make_shared<Foo>(foo)) << '\n'
              << f4(std::make_unique<Foo>(foo)) << '\n';
}
```


#### std::is_bind_expression
若 T 是调用 std::bind 产生的类型，则此模板从 std::true_type 导出。对于任何其他类型，此模板从 std::false_type 导出。
##### 成员常量
![alt text](../Image/is_bind_expression.png)
##### 帮助变量模板
template< class T >
inline constexpr bool is_bind_expression_v = is_bind_expression<T>::value
```cpp
int main() {
    // 假设我们有一个 std::bind 表达式
    auto bound_func = std::bind([](int x, int y) { return x + y; }, 2, 3);
    // 检查是否是 std::bind 表达式的结果
    if constexpr (std::is_bind_expression_v<decltype(bound_func)>) {
        std::cout << "是 std::bind 表达式的结果" << std::endl;
    } else {
        // 不是 std::bind 表达式的结果
    }
    return 0;
}
```

#### std::is_placeholder
![alt text](../Image/is_placeholder.png)
```cpp
 std::cout << "Standard placeholder _5 is for the argument number "
              << std::is_placeholder<decltype(std::placeholders::_5)>::value
              << '\n';
```

# std::mem_fn
函数模板 std::mem_fn 生成指向成员指针的包装对象，它可以存储、复制及调用指向成员指针。到对象的引用和指针（含智能指针）可在调用 std::mem_fn 时使用。
std::mem_fn 是 C++ 标准库中的一个函数模板，它用于创建一个指向成员函数的指针，这样可以将成员函数作为参数传递给算法或者其他函数。
这在需要将成员函数作为回调或者需要存储成员函数指针时非常有用。
```cpp
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

struct Foo {
    int value;
    Foo(int v) : value(v) {}
    void print() const { std::cout << value << ' '; }
};

int main() {
    std::vector<Foo> foos = {Foo(1), Foo(2), Foo(3)};
    // 使用 std::mem_fn 和 for_each 算法
    std::for_each(foos.begin(), foos.end(), std::mem_fn(&Foo::print));
    std::cout << '\n';
    return 0;
}

----------------------------------------------------------------
    auto greet = std::mem_fn(&Foo::display_greeting);
    greet(&f);
 
    auto print_num = std::mem_fn(&Foo::display_number);
    print_num(&f, 42);
 
    auto access_data = std::mem_fn(&Foo::data);
    std::cout << "data: " << access_data(&f) << '\n';
```


