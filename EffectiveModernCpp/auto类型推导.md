
## auto类型推导

1. 情景一：类型说明符是一个指针或引用但不是通用引用
2. 情景二：类型说明符一个通用引用
3. 情景三：类型说明符既不是指针也不是引用

## 数组情况
```cpp
const char name[] =             //name的类型是const char[13]
 "R. N. Briggs";

auto arr1  = name;               //arr1的类型是const char*
auto& arr2 = name;              //arr2的类型是const char (&)[13]

void someFunc(int, double);     //someFunc是一个函数，
                                //类型为void(int, double)

auto func1  = someFunc;          //func1的类型是void (*)(int, double)
auto& func2 = someFunc;         //func2的类型是void (&)(int, double)
```

## auto的特殊初始化方式
```cpp
auto x1 = 27;
auto x2(27);
auto x3 = { 27 };
auto x4   { 27 };
```
这些声明都能通过编译，但是他们不像替换之前那样有相同的意义。前面两个语句确实声明了一个类型为int值为27的变量，但是后面两个声明了一个存储一个元素27的 std::initializer_list<int>类型的变量。

```cpp
auto x1 = 27;                   //类型是int，值是27
auto x2(27);                    //同上
auto x3 = { 27 };               //类型是std::initializer_list<int>，值是{ 27 }
auto x4{ 27 };                  //同上
```

对于花括号的处理是auto类型推导和模板类型推导唯一不同的地方。当使用auto声明的变量使用花括号的语法进行初始化的时候，会推导出std::initializer_list<T>的实例化，但是对于模板类型推导这样就行不通：

```cpp
auto x = { 11, 23, 9 };         //x的类型是std::initializer_list<int>
template<typename T>            //带有与x的声明等价的
void f(T param);                //形参声明的模板
f({ 11, 23, 9 });               //错误！不能推导出T


然而如果在模板中指定T是std::initializer_list<T>而留下未知T,模板类型推导就能正常工作：
template<typename T>
void f(std::initializer_list<T> initList);

f({ 11, 23, 9 });               //T被推导为int，initList的类型为
                                //std::initializer_list<int>
```

!!!note 注意！
auto类型推导通常和模板类型推导相同，但是auto类型推导假定花括号初始化代表std::initializer_list，而模板类型推导不这样做
在C++14中auto允许出现在函数返回值或者lambda函数形参中，但是它的工作机制是模板类型推导那一套方案，而不是auto类型推导


