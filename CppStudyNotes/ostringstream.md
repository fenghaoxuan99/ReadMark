





 stringstream[^1]是C++提供的专门用于处理字符串的输入输出流类。






```cpp
#include <iostream>
#include <sstream>
using namespace std;
int main()
{
    ostringstream ss("1 2 3 4 ", std::ios_base::ate);	// append 方式追加
    cout << ss.str() << endl;
 
    ss << "5 3 4";
    cout << ss.str() << endl;
    
    return 0;
}
/*
输出：
1 2 3 4 
1 2 3 4 5 3 4
*/
```

## 修改、清空 stringstream 内容
 stringstream  的内容可以通过 str() 函数进行修改、清空：
```cpp
#include <iostream>
#include <sstream>
using namespace std;
int main()
{
    stringstream ss("hello string");
    cout << ss.str() << endl;
    // 修改内容
    ss.str("hello stringstream");
    cout << ss.str() << endl;
    // 清空内容
    ss.str("");
    cout << ss.str() << endl;
    return 0;
} 
/*
输出：
fghewoo
123456
 
*/
```


```cpp
#include <iostream>
#include <sstream>
using namespace std;
 
int main()
{
    string source = "abc,123,<!>";
    stringstream ss(source);
    cout << ss.str() << endl;
    
	cout<< endl;
 
    string str;
    while (getline(ss, str, ','))
    {
        cout << str << endl;
    }
 
    return 0;
}
 
/*
输出：
abc,123,<!>
 
abc
123
<!>
*/
```


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



[^1]:[参考资料](https://blog.csdn.net/weixin_45031801/article/details/136921743)