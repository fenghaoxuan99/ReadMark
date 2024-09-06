


std::move和std::forward仅仅是执行转换（cast）的函数（事实上是函数模板）。
std::move无条件的将它的实参转换为右值，而std::forward只在特定情况满足时下进行转换。

```cpp
template<typename T>
decltype(auto) move(T&& param)          //C++14，仍然在std命名空间
{
    using ReturnType = remove_referece_t<T>&&;
    return static_cast<ReturnType>(param);
}


class Annotation {
public:
    explicit Annotation(const std::string text)
    ：value(std::move(text))    //“移动”text到value里；这段代码执行起来
    { … }                       //并不是看起来那样
private:
    std::string value;
};
```
这段代码将数据成员value设置为text的值。text并不是被移动到value，而是被拷贝。诚然，text通过std::move被转换到右值，但是text被声明为const std::string，所以在转换之前，text是一个左值的const std::string，而转换的结果是一个右值的const std::string，但是纵观全程，const属性一直保留。

第一，不要在你希望能移动对象的时候，声明他们为const。对const对象的移动请求会悄无声息的被转化为拷贝操作。
第二点，std::move不仅不移动任何东西，而且它也不保证它执行转换的对象可以被移动。