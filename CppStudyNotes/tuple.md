
类模板 std::tuple 是固定大小的异类值汇集。它是 std::pair 的推广。


### std::make_tuple


1. std::tuple_cat 连接多个元组
 auto t2 = std::tuple_cat(t1, std::make_tuple("Foo", "bar"), t1, std::tie(n));

2. tuple_size 获取元组大小
template< class T >
inline constexpr std::size_t tuple_size_v = tuple_size<T>::value;

```cpp
#include <iostream>
#include <tuple>
 
template <class T>
void test(T t)
{
    int a[std::tuple_size<T>::value]; // 可在编译时
 
    std::cout << std::tuple_size<T>::value << '\n'; // 或在运行时使用
}
 
int main()
{
    test(std::make_tuple(1, 2, 3.14));
}
```



```cpp{.line-numbers}
std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    throw std::invalid_argument("id");
}
 
int main()
{
    auto student0 = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: "   << std::get<0>(student0) << ", "
              << "grade: " << std::get<1>(student0) << ", "
              << "name: "  << std::get<2>(student0) << '\n';
   std::tie(gpa1, grade1, name1) = get_student(1);




       auto t = std::make_tuple(1, "Foo", 3.14);
    // 基于下标的访问
    std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t)
              << ", " << std::get<2>(t) << ")\n";
    // 基于类型的访问（ C++14 起）
    std::cout << "(" << std::get<int>(t) << ", " << std::get<const char*>(t)
              << ", " << std::get<double>(t) << ")\n";
```