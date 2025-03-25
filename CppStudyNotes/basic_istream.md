


# basic_istream
![alt text](../Image/stream.png)

#### std::cin, std::wcin
```cpp
extern std::istream cin;
extern std::wistream wcin;
```
全局对象 std::cin 和 std::wcin 控制来自实现定义的类型（从 std::streambuf 派生）的流缓冲区的输入，该缓冲区与标准 C 输入流 stdin 关联。

#### std::basic_istream<CharT,Traits>::get
```cpp
int_type get();
basic_istream& get( char_type& ch );
basic_istream& get( char_type* s, std::streamsize count );
basic_istream& get( char_type* s, std::streamsize count, char_type delim );
basic_istream& get( basic_streambuf& strbuf );
basic_istream& get( basic_streambuf& strbuf, char_type delim );
```
**从流中提取字符或多个字符**
- ch	 -	写入结果字符的引用
- s	     -	指向用于存储字符的字符串的指针
- count  -	s 指向的字符串的大小
- delim	 -	用于停止提取的分隔符字符。它不会被提取也不会被存储
- strbuf -	用于读取内容的流缓冲区

```cpp
#include <iostream>
#include <sstream>
 
int main()
{
    std::istringstream s1("Hello, world.");
    char c1 = s1.get(); // reads 'H'
    std::cout << "after reading " << c1 << ", gcount() == " <<  s1.gcount() << '\n';
 
    char c2;
    s1.get(c2);         // reads 'e'
    char str[5];
    s1.get(str, 5);     // reads "llo,"
    std::cout << "after reading " << str << ", gcount() == " <<  s1.gcount() << '\n';
 
    std::cout << c1 << c2 << str;
    s1.get(*std::cout.rdbuf()); // reads the rest, not including '\n'
    std::cout << "\nAfter the last get(), gcount() == " << s1.gcount() << '\n';
}
```


#### std::basic_istream<CharT,Traits>::unget
使最近提取的字符再次可用。

```cpp
#include <iostream>
#include <sstream>
 
int main()
{
    std::istringstream s1("Hello, world.");
    char c1 = s1.get();
    if (s1.unget())
    {
        char c2 = s1.get();
        std::cout << "Got: '" << c1 << "'. Got again: '" << c2 << "'.\n";
    }
}
```


#### std::basic_istream<CharT,Traits>::putback
```cpp
basic_istream& putback( char_type ch );
```
**将字符 ch 放回输入流，以便下一个提取的字符将是 ch。** 也就是说符号必须相同。
```cpp
#include <iostream>
#include <sstream>
 
int main()
{
    std::stringstream s1("Hello, world"); // IO stream
    s1.get();
    if (s1.putback('Y')) // modifies the buffer
        std::cout << s1.rdbuf() << '\n';
    else
        std::cout << "putback failed\n";
 
    std::cout << "--\n";
 
    std::istringstream s2("Hello, world"); // input-only stream
    s2.get();
    if (s2.putback('Y')) // cannot modify input-only buffer
        std::cout << s2.rdbuf() << '\n';
    else
        std::cout << "putback failed\n"; 
    s2.clear();
 
    std::cout << "--\n";
 
    if (s2.putback('H')) // non-modifying putback
        std::cout << s2.rdbuf() << '\n';
    else
        std::cout << "putback failed\n";
}
```


#### std::basic_istream<CharT,Traits>::peek
int_type peek();
**在构造和测试哨兵对象之后，从输入流读取下一个字符，但不提取它。**
```cpp
#include <iostream>
#include <sstream>
 
int main()
{
    std::istringstream s1("Hello, world.");
    char c1 = s1.peek();
    char c2 = s1.get();
    std::cout << "Peeked: " << c1 << " got: " << c2 << '\n';
}
```

#### std::basic_istream<CharT,Traits>::getline
```cpp
basic_istream& getline( char_type* s, std::streamsize count );

basic_istream& getline( char_type* s, std::streamsize count, char_type delim );
```
从流中提取字符，直到行尾或指定的定界符 delim。
```cpp
#include <array>
#include <iostream>
#include <sstream>
#include <vector>
 
int main()
{
    std::istringstream input("abc|def|gh");
    std::vector<std::array<char, 4>> v;
 
    // note: the following loop terminates when std::ios_base::operator bool()
    // on the stream returned from getline() returns false
    for (std::array<char, 4> a; input.getline(&a[0], 4, '|');)
        v.push_back(a);
 
    for (auto& a : v)
        std::cout << &a[0] << '\n';
}
```

#### std::basic_istream<CharT,Traits>::read
```cpp
basic_istream& read( char_type* s, std::streamsize count );
```
从流中提取字符。

s	-	指向字符数组的指针，用于存储要读取的字符
count	-	要读取的字符数
```cpp
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
 
int main()
{
    // read() is often used for binary I/O
    std::string bin = {'\x12', '\x12', '\x12', '\x12'};
    std::istringstream raw(bin);
    std::uint32_t n;
    if (raw.read(reinterpret_cast<char*>(&n), sizeof n))
        std::cout << std::hex << std::showbase << n << '\n';
 
    // prepare file for next snippet
    std::ofstream("test.txt", std::ios::binary) << "abcd1\nabcd2\nabcd3";
 
    // read entire file into string
    if (std::ifstream is{"test.txt", std::ios::binary | std::ios::ate})
    {
        auto size = is.tellg();
        std::string str(size, '\0'); // construct string to stream size
        is.seekg(0);
        if (is.read(&str[0], size))
            std::cout << str << '\n';
    }
}
```

#### std::basic_istream<CharT,Traits>::readsome
```cpp
std::streamsize readsome( char_type* s, std::streamsize count );
```
从输入流中提取最多 count 个立即可用的字符。 提取的字符存储到 s 指向的字符数组中。
参数
s	-	指向用于存储字符的字符数组的指针
count	-	要读取的最大字符数

#### std::basic_istream<CharT,Traits>::gcount
```cpp
std::streamsize gcount() const;
```
返回上一次非格式化输入操作提取的字符数，如果该数字无法表示，则返回 std::streamsize 的最大可表示值。



#### std::basic_istream<CharT,Traits>::ignore
```cpp
basic_istream& ignore( std::streamsize count = 1, int_type delim = Traits::eof() );
```
**从输入流中提取并丢弃字符，直到遇到定界符 delim（包括定界符）。**
参数：
count：要跳过的最大字符数（默认为 1）。
delim：分隔符，遇到此字符时停止跳过（默认为 Traits::eof()，即文件结束符）。

##### 清除输入缓冲区残留字符
当混合使用 operator>> 和 getline 时，输入缓冲区可能残留换行符（\n），导致后续 getline 直接读取空字符串。
```cpp
int age;
std::string name;

std::cout << "输入年龄：";
std::cin >> age;            // 输入后缓冲区残留换行符 '\n'

// 清除换行符
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

std::cout << "输入姓名：";
std::getline(std::cin, name); // 正常读取
```

###### 跳过无效输入
当输入格式不符合预期时（如输入非数字字符到 int 变量），需清除错误状态并清空缓冲区。
示例：
```cpp
int value;
while (true) {
    std::cout << "输入一个整数：";
    if (std::cin >> value) {
        break; // 输入有效
    } else {
        std::cin.clear(); // 清除错误状态
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空缓冲区
        std::cout << "输入无效，请重试！\n";
    }
}
```


###### 快速跳过整行输入
直接跳过当前行的所有剩余字符（直到换行符）。
示例：
```CPP
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过整行
```

###### 限制跳过的字符数
仅跳过固定数量的字符（不依赖分隔符）。
示例：

```CPP
// 输入 "ABCDEFGHI"
std::cin.ignore(5); // 跳过前5个字符（"ABCDE"）
char c;
std::cin >> c;      // c = 'F'
```