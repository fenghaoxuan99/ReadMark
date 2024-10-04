


<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [std::optional](#stdoptional)
      - [std::optional<T>::value](#stdoptionaltvalue)
      - [std::optional<T>::value_or](#stdoptionaltvalue_or)
      - [void reset() noexcept;](#void-reset-noexcept)
      - [std::optional<T>::swap](#stdoptionaltswap)
      - [std::make_optional](#stdmake_optional)
      - [std::optional<T>::emplace](#stdoptionaltemplace)
      - [std::optional<T>::operator bool, std::optional<T>::has_value](#stdoptionaltoperator-bool-stdoptionalthas_value)

<!-- /code_chunk_output -->

# std::optional
std::optional 是C++17标准中引入的一个模板类，它用于表示一个可选值，即一个值可以存在也可以不存在。
这使得它非常适合于那些可能没有值的情况，比如函数返回值，或者表示一个可能失败的操作的结果。
一种常见的 optional 使用情况是一个可能失败的函数的返回值

任何一个 optional<T> 的实例在给定时间点要么含值，要么不含值。
若一个 optional<T> 含值，则保证值作为 optional 对象所用空间的一部分分配，即不会发生动态内存分配。


#### std::optional<T>::value
若 *this 含值，则返回到所含值引用。
否则，抛出 std::bad_optional_access 异常。


#### std::optional<T>::value_or
template< class U >
constexpr T value_or( U&& default_value ) &&;
default_value	-	用于 *this 为空情况的值
```cpp
1. 等价于 bool(*this) ? **this : static_cast<T>(std::forward<U>(default_value))
2. 等价于 bool(*this) ? std::move(**this) : static_cast<T>(std::forward<U>(default_value))
std::optional<const char*> maybe_getenv(const char* n)
{
    if(const char* x = std::getenv(n))
       return x;
    else
       return {};
}
int main()
{
     std::cout << maybe_getenv("MYPWD").value_or("(none)") << '\n';
}
```

#### void reset() noexcept;
若 *this 含值，则如同用 value().T::~T() 销毁此值。否则无效果。

#### std::optional<T>::swap
void swap( optional& other ) noexcept
与 other 交换内容。
若 *this 和 other 均不含值，则函数无效果。
若 *this 与 other 仅有一个含值（称此对象为 in ，另一者为 un ），则从 std::move(*in) 直接初始化 un 所含值，随后如同通过 in->T::~T() 析构 in 所含值。此调用后， in 不含值； un 含值。
若 *this 与 other 均含值，则通过调用 std::swap(**this, *other) 交换所含值。 T 左值必须满足可交换 (Swappable) 。

#### std::make_optional
1. template< class T >
constexpr std::optional<std::decay_t<T>> make_optional( T&& value );

从value 创建 optional 对象。等效地调用 std::optional<std::decay_t<T>>(std::forward<T>(value)) 。


#### std::optional<T>::emplace
1. template< class... Args >
T& emplace( Args&&... args );

2. template< class U, class... Args >
T& emplace( std::initializer_list<U> ilist, Args&&... args );

```cpp
#include <optional>
#include <iostream>
#include <string>

class Widget {
public:
    Widget(int x) {
        std::cout << "Widget constructed with value: " << x << std::endl;
    }
    ~Widget() {
        std::cout << "Widget destructed" << std::endl;
    }
};

int main() {
    std::optional<Widget> opt;

    // 构造一个 Widget 对象
    opt.emplace(42);

    // 销毁当前 Widget 对象，并构造一个新的 Widget 对象
    opt.emplace(99);

    return 0;
}
```


#### std::optional<T>::operator bool, std::optional<T>::has_value
1. constexpr explicit operator bool() const noexcept;
2. constexpr bool has_value() const noexcept;
```cpp
    std::optional<int> optional_with_value = 10;
    std::optional<int> optional_without_value;

    // 使用 operator bool 进行 if 条件判断
    if (optional_with_value) {
        std::cout << "optional_with_value contains a value: " << *optional_with_value << std::endl;
    } else {
        std::cout << "optional_with_value is empty" << std::endl;
    }

    // 使用 has_value 成员函数进行 if 条件判断
    if (optional_without_value.has_value()) {
        std::cout << "optional_without_value contains a value" << std::endl;
    } else {
        std::cout << "optional_without_value is empty" << std::endl;
    }
```