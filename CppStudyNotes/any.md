

# std::any
类any描述用于任何类型的单个值的类型安全容器。

1. 类 any 的对象存储任何满足构造函数要求的类型的一个实例或为空，而这被称为 any 类对象的状态。存储的实例被称作所含对象。若两个状态均为空，或均为非空且其所含对象等价，则两个状态等价。
2. 非成员 any_cast 函数提供对所含对象的类型安全访问。

std::any 是C++17标准中引入的一个模板类，它提供了一种存储任意类型值的方式，并且可以在运行时检查和转换存储的值。std::any 可以看作是一个“类型安全的变体”，它允许你将任何类型的对象存储在一个单一的变量中。

- 类型擦除：std::any 使用类型擦除技术，这意味着它不暴露存储值的具体类型。
- 异常安全：std::any 的操作是异常安全的，即使在构造或赋值时发生异常，也不会泄露资源。
- 复制和移动：std::any 支持复制和移动操作。复制一个 std::any 对象会复制它包含的值（如果该值是可复制的）。移动一个 std::any 对象会转移它包含的值（如果该值是可移动的）。

#### 检查和访问值：
- has_value()：返回一个布尔值，指示 std::any 是否包含值。
- type()：返回一个 std::type_info 对象，表示存储值的类型。
- reset()：清空 std::any，使其不包含任何值。
访问和转换值：

any_cast<T>(const any&)：将 std::any 对象转换为指定类型 T 的引用。
any_cast<T>(any&&)：将 std::any 对象转换为指定类型 T 的右值引用。
==celestial.emplace<Star>("Procyon", 2943);==

#### std::any::reset
若非空，则销毁所含对象。
```cpp
#include <any>
#include <cassert>
 
int main()
{
    std::any a{42};
    assert(a.has_value());
    a.reset();
    assert(not a.has_value());
}
```


#### std::make_any
```cpp
template< class T, class... Args >
std::any make_any( Args&&... args );

template< class T, class U, class... Args >
std::any make_any( std::initializer_list<U> il, Args&&... args );
```
构造一个 any 对象，其中包含 T 类型的对象，并将提供的参数传递给 T 的构造函数。

```cpp
std::any a = std::make_any<int>(42);
std::any b = std::make_any<std::string>("Hello, world!");
```


#### std::any::emplace
```cpp
template< class ValueType, class... Args >
std::decay_t<ValueType>& emplace( Args&&... args );
```
**将包含的对象更改为从参数构造的 std::decay_t<ValueType> 类型的对象。**
```cpp
std::any a;
a.emplace<int>(42);
a.emplace<std::string>("Hello, world!");
```


#### std::any::type
const std::type_info& type() const noexcept;
若实例非空则为所含值的 typeid ，否则为 typeid(void) 。

#### std::any_cast
执行对包含对象的类型安全访问。
```cpp
template< class T >
T& any_cast( any& operand );
```
若 operand 为空或所含对象不是 T 类型，则抛出 std::bad_any_cast 异常。

```cpp
  if (int* i = std::any_cast<int>(&a)) {
       std::cout << "a is int: " << *i << '\n';
    } else if (std::string* s = std::any_cast<std::string>(&a)) {
       std::cout << "a is std::string: " << *s << '\n';
    } else {
       std::cout << "a is another type or unset\n";
    }
```


```cpp{.line-numbers}
#include <any>
#include <iostream>
 
int main()
{
    std::cout << std::boolalpha;
 
    // any 类型
    std::any a = 1;
    std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
    a = 3.14;
    std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
    a = true;
    std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';
 
    // 有误的转型
    try
    {
        a = 1;
        std::cout << std::any_cast<float>(a) << '\n';
    }
    catch (const std::bad_any_cast& e)
    {
        std::cout << e.what() << '\n';
    }
 
    // 拥有值
    a = 1;
    if (a.has_value())
    {
        std::cout << a.type().name() << '\n';
    }
 
    // 重置
    a.reset();
    if (!a.has_value())
    {
        std::cout << "no value\n";
    }
 
    // 指向所含数据的指针
    a = 1;
    int* i = std::any_cast<int>(&a);
    std::cout << *i << "\n";
}
```