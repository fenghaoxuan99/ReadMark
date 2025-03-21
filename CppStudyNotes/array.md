


# std::array

```cpp
template< class T,std::size_t N> struct array;
```
**std::array 是封装固定大小数组的容器。**
此容器是一个聚合类型，其语义等同于保有一个 C 风格数组 T[N] 作为其唯一非静态数据成员的结构体。不同于 C 风格数组，它不会自动退化成 T* 。
它能作为聚合类型聚合初始化，只要有至多 N 个能转换成 T 的初始化器： std::array<int, 3> a = {1,2,3}; 。
该结构体结合了 C 风格数组的性能、可访问性与容器的优点，比如可获取大小、支持赋值、随机访问迭代器等。


### 访问元素


|元素访问| 元素访问|
|--|--|
|**at**        |访问指定的元素，同时进行越界检查。|
|**operator[]**|访问指定的元素，不进行越界检查。|
|**front**     |访问第一个元素。|
|**back**      |访问最后一个元素。|
|**data**      |直接访问底层数组。|

### std::get(std::array)
```cpp
#include <iostream>
#include <array>
 
int main()
{
    std::array<int, 3> arr;
 
    // 设置值：
    std::get<0>(arr) = 1;
    std::get<1>(arr) = 2;
    std::get<2>(arr) = 3;
 
    // 获取值：
    std::cout << "(" << std::get<0>(arr) << ", " << std::get<1>(arr)
              << ", " << std::get<2>(arr) << ")\n";
}
```

### std::array<T,N>::fill()  填充容器
```cpp
#include <array>
#include <iostream>
 
int main()
{
    constexpr int xy = 4;
 
    using Cell = std::array<unsigned char, 8>;
 
    std::array<Cell, xy * xy> board;
 
    board.fill({ {0xE2, 0x96, 0x84, 0xE2, 0x96, 0x80, 0, 0} }); // "▄▀";
 
    for (unsigned i = 0; i != board.size();) {
        std::cout << board[i].data();
        if ((++i % xy) == 0) {
            std::cout.put('\n');
        }
    }
}
```