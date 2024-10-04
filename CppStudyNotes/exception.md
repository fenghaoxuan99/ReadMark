








```cpp
try {
    std::string("abc").substr(10); // 抛出 std::length_error
} catch(const std::exception& e) {
    std::cout << e.what() << '\n';
//  throw e; // 复制初始化一个 std::exception 类型的新异常对象
    throw;   // 重抛 std::length_error 类型的异常对象
}
```

throw 表达式被归类为 void 类型的纯右值表达式。与任何其他表达式一样，它可以是另一表达式中的子表达式，最常见于条件运算符：
```cpp
double f(double d)
{
    return d > 1e7 ? throw std::overflow_error("too big") : d;
}
int main()  
{
    try {
        std::cout << f(1e10) << '\n';
    } catch (const std::overflow_error& e) {
        std::cout << e.what() << '\n';
    }
}
```