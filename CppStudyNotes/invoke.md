

# std::invoke 
std::invoke 是 C++17 标准中引入的一个模板函数，它用于以最直观的方式调用给定的
**可调用对象（函数、函数指针、成员函数指针、std::function、lambda 表达式等）。**
这个函数的目的是提供一个统一的接口来调用不同类型的可调用对象，而不需要关心它们的具体类型。

### 语法
```cpp
template< class F, class... Args >
invoke_result_t<F, Args...> invoke( F&& f, Args&&... args );
```

- `F` 是可调用对象的类型。
- `Args...` 是传递给可调用对象的参数类型。
- `invoke_result_t` 是调用结果的类型，它是 `std::invoke_result` 类型的别名。

### 使用示例
**核心示例：**
```cpp
struct X {
    int data = 100;
    void print(int add) { std::cout << data + add << std::endl; }
};

int main() {
    X x;
    // 调用成员函数
    std::invoke(&X::print, x, 50);    // 输出 150
    // 访问成员变量
    int d = std::invoke(&X::data, x); // d = 100
}
```
通过 `std::invoke`，可以统一处理函数、成员函数、成员变量等调用方式，显著提升泛型代码的灵活性和简洁性。





#### 调用普通函数

```cpp
#include <iostream>
#include <functional>

void foo(int x) {
    std::cout << x << std::endl;
}

int main() {
    std::invoke(foo, 42); // 输出: 42
    return 0;
}
```

#### 调用成员函数

**第一个参数为对象实例（对象、指针、引用或 std::reference_wrapper）**

```cpp
#include <iostream>
#include <functional>

struct Foo {
    void bar(int x) {
        std::cout << x << std::endl;
    }
};

int main() {
    Foo foo;
    
    std::invoke(&Foo::bar, foo, 42);           // 输出: 42
    std::invoke(&Foo::bar, &foo, 12);          // 输出: 42
    std::invoke(&Foo::bar, std::ref(foo), 12); // 输出: 42
    return 0;
}
```


#### 成员变量
返回成员变量的引用：

```CPP
struct Z { int val; };
Z z{10};
int v = std::invoke(&Z::val, z); // v = 10
```





#### 调用成员函数指针

```cpp
#include <iostream>
#include <functional>

struct Foo {
    void bar(int x) {
        std::cout << x << std::endl;
    }
};

int main() {
    Foo foo;
    std::invoke(&Foo::bar, &foo, 42); // 输出: 42
    return 0;
}
```
#### 在泛型编程中的应用
统一处理可调用对象，无需针对类型编写特化代码：

```CPP
template<typename Callable, typename... Args>
auto callAndLog(Callable&& func, Args&&... args) {
    auto result = std::invoke(std::forward<Callable>(func), 
                              std::forward<Args>(args)...);
    std::cout << "Result: " << result << std::endl;
    return result;
}

// 可调用任何函数、成员函数或成员变量
callAndLog(foo, 42);
callAndLog(&Y::meth, y, 42);
callAndLog(&Z::val, z);
```


#### 调用 std::function

```cpp
#include <iostream>
#include <functional>

int main() {
    std::function<void(int)> func = [](int x) { std::cout << x << std::endl; };
    std::invoke(func, 42); // 输出: 42
    return 0;
}
```

#### 调用 lambda 表达式

```cpp
#include <iostream>
#include <functional>

int main() {
    auto lambda = [](int x) { std::cout << x << std::endl; };
    std::invoke(lambda, 42); // 输出: 42
    return 0;
}
```

`std::invoke` 的好处是它提供了一种统一的方式来调用不同类型的可调用对象，而不需要担心它们的具体类型。这在编写泛型代码或标准库算法时特别有用，因为你可以确保以一致的方式调用任何类型的可调用对象。

### 注意事项

- `std::invoke` 可以完美转发参数的 `std::ref` 和 `std::cref`，这意味着它可以用来调用需要引用或 const 引用参数的函数。
- 如果可调用对象是一个成员函数指针，第一个参数应该是对象的实例，第二个参数是成员函数指针，后续参数是传递给成员函数的参数。
- `std::invoke` 可以处理成员函数的引用资格，这意味着它可以调用 `&Foo::bar`，无论 `bar` 是一个普通成员函数还是一个 const 或 volatile 成员函数。
