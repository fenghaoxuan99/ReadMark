


# std::greater

#### std::greater::operator()
```cpp
constexpr bool operator()(const T &lhs, const T &rhs) const 
{
    return lhs > rhs;
}
```
**检查 lhs 是否大于 rhs**


# std::less
#### std::less::operator()
```cpp
constexpr bool operator()(const T &lhs, const T &rhs) const 
{
    return lhs < rhs;
}
```
**检查 lhs 是否小于 rhs**



```cpp
#include <functional>
#include <iostream>
 
template <typename A, typename B, typename U = std::less<>>
bool f(A a, B b, U u = U())
{
    return u(a, b);
}
 
int main() 
{
    std::cout << std::boolalpha;   
    std::cout << f(5, 20) << '\n';
    std::cout << f(100, 10) << '\n';
}
```