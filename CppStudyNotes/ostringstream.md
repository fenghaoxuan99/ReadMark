

# std::ostringstream
std::ostringstream 是 C++ 标准库中的一个输出字符串流类，它可以用于将各种数据类型转换为字符串，并且支持格式控制和字符串拼接操作。
## 头文件
#include <sstream>

## 基本用法
最基本的用法是创建 std::ostringstream 对象并使用流操作符 << 将数据插入流中，然后通过 str() 方法获取流中的字符串表示。
```cpp{.line-numbers}
std::ostringstream oss;
int num = 42;
double pi = 3.14159;
oss << "Number: " << num << ", Pi: " << pi;
std::string result = oss.str();
```

2. 格式控制
可以使用控制符控制字符串的格式，比如设置精度、固定小数位数等。
```cpp{.line-numbers}
std::ostringstream oss;
double pi = 3.14159;
oss << std::fixed << std::setprecision(2) << pi; // 设置精度为2位小数
std::string piStr = oss.str(); // 将输出保留两位小数

将num输出为20位的数据，不足20位的补0
long num = 11111;
oss << std::setw(20) << std::setfill('0') << num;
```

3. 清空和重置
可以使用 str("") 方法清空流中的内容，或者使用 str(newStr) 方法重置流中的内容为新的字符串。]
```cpp{.line-numbers}
std::ostringstream oss;
oss << "Hello, ";
oss.str(""); // 清空流中的内容
oss << "World!";
std::string result = oss.str(); // result 现在是 "World!"
```
