


# std::reference_wrapper
std::reference_wrapper 是 C++ 标准库 <functional> 头文件中提供的一个模板类，用于将引用包装成一个可复制、可赋值的对象。它的核心目的是在需要按值传递的上下文中（如泛型算法、容器、线程等）模拟引用的语义，从而避免不必要的拷贝并允许修改原始对象。

```cpp
template< class T >
class reference_wrapper;
```
- std::reference_wrapper 是包装引用于可复制、可赋值对象的类模板。
- 它用于包装一个引用，使得可以将引用存储在容器中或作为函数的参数传递。

get()：显式获取底层引用。


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


    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);
 
    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());

#include <vector>
#include <functional>
#include <iostream>

int main() {
    int a = 1, b = 2, c = 3;
    std::vector<std::reference_wrapper<int>> vec{ std::ref(a), std::ref(b), std::ref(c) };
    for (auto& ref : vec) ref.get() *= 2; // 修改原始对象
    std::cout << a << ", " << b << ", " << c << std::endl; // 输出 2, 4, 6
}
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




## `std::ref()` 和 `std::cref()` 是 C++ 标准库中用于创建引用包装器的工具
主要解决函数对象（如通过 `std::bind`、`std::thread` 或算法传递时）默认值传递的问题。：


### **1. 核心作用**
- **`std::ref()`**： 生成一个**非 const 引用包装器**（`std::reference_wrapper<T>`），允许被引用的对象在函数中被修改。
- **`std::cref()`**：生成一个**const 引用包装器**（`std::reference_wrapper<const T>`），确保被引用的对象在函数中不可修改。

它们属于 `<functional>` 头文件，用于在需要引用传递的上下文中避免不必要的拷贝。


### **2. 使用场景**
当以下情况需要传递引用而非拷贝时：
- 使用 `std::bind` 绑定参数。
- 创建 `std::thread` 或 `std::async` 时传递参数。
- 传递参数给接受通用引用的函数模板（如 `std::make_tuple`）。


### **3. 用法示例**

#### **示例 1：`std::thread` 中的引用传递**
```cpp
#include <iostream>
#include <thread>
#include <functional>

void modify(int& x) {
    x = 42;
}

void read(const int& x) {
    std::cout << "Value: " << x << std::endl;
}

int main() {
    int a = 0;
    int b = 0;

    // 错误：默认值传递，无法修改外部变量 a
    std::thread t1(modify, a);
    t1.join();
    std::cout << a << std::endl; // 输出 0

    // 正确：通过 std::ref 传递引用
    std::thread t2(modify, std::ref(a));
    t2.join();
    std::cout << a << std::endl; // 输出 42

    // 正确：通过 std::cref 传递 const 引用
    std::thread t3(read, std::cref(b));
    t3.join(); // 输出 Value: 0
}
```

#### **示例 2：`std::bind` 中的引用绑定**
```cpp
#include <iostream>
#include <functional>

void update(int& x) {
    x *= 2;
}

int main() {
    int val = 10;
    auto func1 = std::bind(update, val); // 值传递，无法修改 val
    func1();
    std::cout << val << std::endl; // 输出 10

    auto func2 = std::bind(update, std::ref(val)); // 引用传递
    func2();
    std::cout << val << std::endl; // 输出 20
}
```

---

### **4. 区别总结**
| 特性               | `std::ref()`                | `std::cref()`                     |
|-------------------|-----------------------------|-----------------------------------|
| **引用类型**       | 非 const 引用 (`T&`)         | const 引用 (`const T&`)          |
| **是否允许修改对象**| 是                           | 否                                |
| **返回类型**       | `std::reference_wrapper<T>` | `std::reference_wrapper<const T>` |
| **隐式转换目标**    | `T&`                        | `const T&`                        |

---

### **5. 注意事项**
1. **生命周期管理**：确保被引用对象的生命周期长于引用包装器的使用时间，避免悬垂引用。
2. **类型匹配**：
   - `std::cref()` 不能传递给接受非 const 引用的函数。
   - 若函数参数为值类型，`std::ref`/`std::cref` 会被隐式解引用并拷贝。
3. **底层实现**：
   - `std::reference_wrapper` 本质保存指针，支持复制和赋值（复制后指向同一对象）。
   - 可通过 `.get()` 显式获取原始引用，或隐式转换为 `T&`/`const T&`。

---

### **6. 适用场景对比**
- **`std::ref()`**： 需在函数内部修改外部变量时  （如线程间共享数据）。
- **`std::cref()`**：仅需读取数据且希望避免拷贝时（如传递大型只读对象）。
