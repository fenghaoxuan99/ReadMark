


# std::reference_wrapper
1. template< class T >
class reference_wrapper;
- std::reference_wrapper 是包装引用于可复制、可赋值对象的类模板。
- 它用于包装一个引用，使得可以将引用存储在容器中或作为函数的参数传递。

![alt text](../Image/reference_wrapper.png)
```cpp
    int a = 10;
    std::reference_wrapper<int> ref_a(a);
    // 通过引用包装器访问原始对象
    std::cout << ref_a.get() << std::endl; // 输出: 10
    std::cout << ref_a << std::endl;       // 输出: 10，调用了 operator T&()

    // 修改原始对象
    ref_a.get() = 20;
    std::cout << a << std::endl; // 输出: 20

-----------------------------------------------------------
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);
 
    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());
```


# ref
函数模板 ref 与 cref 是生成 std::reference_wrapper 类型对象的帮助函数，它们用模板实参推导确定结果的模板实参。

```cpp
#include <functional>
#include <iostream>
 
void f(int& n1, int& n2, const int& n3)
{
    std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    ++n1; // 增加存储于函数对象的 n1 副本
    ++n2; // 增加 main() 的 n2
    // ++n3; // 编译错误
}
 
int main()
{
    int n1 = 1, n2 = 2, n3 = 3;
    std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
    n1 = 10;
    n2 = 11;
    n3 = 12;
    std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    bound_f();
    std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
}
```