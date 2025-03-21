

# std::initializer_list

1. template< class T >
class initializer_list;

std::initializer_list<T> 类型对象是一个访问 const T 类型对象数组的轻量代理对象。

#### std::initializer_list 对象在这些时候自动构造：
1. 用花括号初始化器列表列表初始化一个对象，其中对应构造函数接受一个 std::initializer_list 参数
2. 以花括号初始化器列表为赋值的右运算数，或函数调用参数，而对应的赋值运算符/函数接受 std::initializer_list 参数
3. 绑定花括号初始化器列表到 auto ，包括在范围 for 循环中

```cpp{.line-numbers}
#include <iostream>
#include <initializer_list>
 
int main() 
{
    std::initializer_list<int> empty_list;
    std::cout << "empty_list.size(): " << empty_list.size() << '\n';
 
    // 用列表初始化创建初始化器列表
    std::initializer_list<int> digits {1, 2, 3, 4, 5};
    std::cout << "digits.size(): " << digits.size() << '\n';
 
    // auto 的特殊规则表示‘ fraction ’拥有类型
    // type std::initializer_list<double>
    auto fractions = {3.14159, 2.71828};
    std::cout << "fractions.size(): " << fractions.size() << '\n';
}
```

```cpp
#include <iostream>
#include <vector>
#include <initializer_list>
 
template <class T>
struct S {
    std::vector<T> v;
    S(std::initializer_list<T> l) : v(l) {
         std::cout << "constructed with a " << l.size() << "-element list\n";
    }
    void append(std::initializer_list<T> l) {
        v.insert(v.end(), l.begin(), l.end());
    }
    std::pair<const T*, std::size_t> c_arr() const {
        return {&v[0], v.size()};  // 在 return 语句中复制列表初始化
                                   // 这不使用 std::initializer_list
    }
};
 
template <typename T>
void templated_fn(T) {}
 
int main()
{
    S<int> s = {1, 2, 3, 4, 5}; // 复制初始化
    s.append({6, 7, 8});      // 函数调用中的列表初始化
 
    std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";
 
    for (auto n : s.v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    std::cout << "Range-for over brace-init-list: \n";
 
    for (int x : {-1, -2, -3}) // auto 的规则令此带范围 for 工作
        std::cout << x << ' ';
    std::cout << '\n';
 
    auto al = {10, 11, 12};   // auto 的特殊规则
 
    std::cout << "The list bound to auto has size() = " << al.size() << '\n';
 
//    templated_fn({1, 2, 3}); // 编译错误！“ {1, 2, 3} ”不是表达式，
                             // 它无类型，故 T 无法推导
    templated_fn<std::initializer_list<int>>({1, 2, 3}); // OK
    templated_fn<std::vector<int>>({1, 2, 3});           // 也 OK
}
```




`std::initializer_list` 是 C++11 引入的一种轻量级容器类模板，用于简化对象的初始化操作。
它允许通过花括号 `{}` 语法将一组值直接传递给函数或构造函数，常用于初始化容器（如 `std::vector`、`std::list`）或自定义类型。

### **核心特性**
1. **轻量级容器**：仅包含指向初始化数据的指针和元素数量，不管理内存。
2. **只读访问**：元素不可修改，只能读取。
3. **隐式构造**：花括号 `{}` 会自动生成 `std::initializer_list` 对象。
4. **生命周期**：其底层数据与花括号初始化列表的生命周期一致（通常是临时对象）。

---

### **基本用法**

#### **1. 初始化标准容器**
标准库容器（如 `std::vector`、`std::map`）提供了接受 `std::initializer_list` 的构造函数，使得初始化更简洁：
```cpp
#include <vector>
#include <string>

std::vector<int> nums = {1, 2, 3, 4}; // 隐式使用 initializer_list
std::vector<std::string> words {"apple", "banana"};
```

#### **2. 自定义类型的初始化**
若自定义类定义了接受 `std::initializer_list` 的构造函数，则可以用 `{}` 初始化：
```cpp
#include <initializer_list>
#include <iostream>

class MyContainer {
public:
    MyContainer(std::initializer_list<int> list) {
        for (int x : list) {
            std::cout << x << " ";
        }
    }
};

MyContainer c = {10, 20, 30}; // 输出：10 20 30
```

#### **3. 函数参数传递**
函数可以直接接受 `std::initializer_list` 作为参数：
```cpp
#include <initializer_list>

void print(std::initializer_list<std::string> list) {
    for (const auto& s : list) {
        std::cout << s << " ";
    }
}

print({"Hello", "World"}); // 输出：Hello World
```

---

### **关键操作**
#### **1. 遍历元素**
使用范围 for 循环或迭代器访问元素：
```cpp
std::initializer_list<int> list = {1, 2, 3};

// 范围 for 循环
for (int x : list) {
    std::cout << x << " ";
}

// 迭代器
auto it = list.begin();
while (it != list.end()) {
    std::cout << *it++ << " ";
}
```

#### **2. 获取元素数量和内容**
```cpp
size_t size = list.size();  // 元素数量（3）
int first = *list.begin();  // 第一个元素（1）
```

---

### **与构造函数的交互**
#### **1. 构造函数重载优先级**
若一个类同时定义了接受 `std::initializer_list` 和其他参数的构造函数，编译器会优先匹配 `std::initializer_list`：
```cpp
class Example {
public:
    Example(int a, int b) { /* ... */ }          // 构造函数1
    Example(std::initializer_list<int>) { /* ... */ } // 构造函数2
};

Example e1(1, 2);   // 调用构造函数1
Example e2{1, 2};    // 调用构造函数2
Example e3({1, 2});  // 调用构造函数2
```

#### **2. 初始化冲突**
某些情况下，`std::initializer_list` 可能导致意外的构造函数调用：
```cpp
std::vector<int> v1(3, 5);   // 3个元素，每个值为5 → [5,5,5]
std::vector<int> v2{3, 5};   // 使用initializer_list → [3,5]
```

---

### **使用场景**
1. **简化容器初始化**：
   ```cpp
   std::map<int, std::string> m = {{1, "one"}, {2, "two"}};
   ```
2. **可变参数函数的替代**：
   ```cpp
   void log(std::initializer_list<const char*> messages) {
       for (auto msg : messages) std::cout << msg << "\n";
   }
   log({"Error: ", "File not found."});
   ```
3. **数值计算中的多参数传递**：
   ```cpp
   Matrix mat = {{1, 2}, {3, 4}}; // 初始化矩阵
   ```

---

### **注意事项**
1. **元素不可修改**：
   ```cpp
   std::initializer_list<int> list = {1, 2, 3};
   // *list.begin() = 10; // 错误：元素是 const 的
   ```
2. **生命周期问题**：
   ```cpp
   auto get_list() {
       return {1, 2, 3}; // 返回的 initializer_list 可能指向已销毁的临时数据
   }
   ```
3. **性能优化**：
   - 对于大型数据，直接传递 `std::initializer_list` 可能比拷贝容器更高效。

---

### **示例代码**
#### **自定义类的初始化**
```cpp
#include <initializer_list>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<int>> data;
public:
    Matrix(std::initializer_list<std::initializer_list<int>> rows) {
        for (auto& row : rows) {
            data.emplace_back(row);
        }
    }
};

Matrix mat = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
```

#### **函数参数传递**
```cpp
#include <initializer_list>
#include <iostream>

void print_squares(std::initializer_list<int> list) {
    for (int x : list) {
        std::cout << x * x << " ";
    }
}

int main() {
    print_squares({1, 2, 3, 4}); // 输出：1 4 9 16
    return 0;
}
```
