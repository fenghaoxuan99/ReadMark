


# basic_istream


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