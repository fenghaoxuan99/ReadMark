
# std::ios_base


![](../Image/isobase.png)
**类 ios_base 是一个多用途类，它是所有 I/O 流类的基类** ,它维护几种数据：

1. 状态信息：流状态标志。
2. 控制信息：控制输入和输出序列格式化的标志以及被注入的区域设置。
3. 私有存储：索引可扩展数据结构，允许 long 和 void* 成员，这可以实现为两个任意长度的数组或一个包含双元素结构体的数组或另一个容器。
4. 回调：从 imbue()、std::basic_ios::copyfmt() 和 ~ios_base() 调用的任意数量的用户定义函数。

#### std::ios_base::flags
```cpp
fmtflags flags() const;

fmtflags flags( fmtflags flags );
```
管理格式标志。

1) 返回当前的格式化设置
2) 用给定的设置替换当前的设置。


#### std::ios_base::setf
#### std::ios_base::unsetf
```cpp
fmtflags setf( fmtflags flags );

fmtflags setf( fmtflags flags, fmtflags mask );

void unsetf( fmtflags flags );
```
将格式化标志设置为指定的设置。
flags, mask	-	新的格式化设置。 mask 定义了可以更改哪些标志，flags 定义了要更改的标志中应设置哪些标志（其他标志将被清除）。 
两个参数都可以是格式化标志常量的组合
```cpp
include <iomanip>
#include <iostream>
#include <numbers>
 
int main()
{
    const double PI = std::numbers::pi;
    const int WIDTH = 15;
 
    std::cout.setf(std::ios::right); // equivalent: cout << right;
    std::cout << std::setw(WIDTH / 2) << "radius"
              << std::setw(WIDTH) << "circumference" << '\n';
 
    std::cout.setf(std::ios::fixed); // equivalent: cout << fixed;
    for (double radius = 1; radius <= 6; radius += 0.5)
        std::cout << std::setprecision(1) << std::setw(WIDTH / 2)
                  << radius
                  << std::setprecision(2) << std::setw(WIDTH)
                  << (2 * PI * radius) << '\n';
}
```

#### std::ios_base::fmtflags
指定可用的格式化标志。
```cpp
typedef /*实现定义*/ fmtflags;
static constexpr fmtflags dec       = /*实现定义*/
static constexpr fmtflags oct       = /*实现定义*/
static constexpr fmtflags hex       = /*实现定义*/
static constexpr fmtflags basefield = dec | oct | hex;
------------------------------------------------------------------
static constexpr fmtflags left        = /*实现定义*/
static constexpr fmtflags right       = /*实现定义*/
static constexpr fmtflags internal    = /*实现定义*/
static constexpr fmtflags adjustfield = left | right | internal;
------------------------------------------------------------------
static constexpr fmtflags scientific  = /*实现定义*/
static constexpr fmtflags fixed       = /*实现定义*/
static constexpr fmtflags floatfield  = scientific | fixed;
------------------------------------------------------------------
static constexpr fmtflags boolalpha  = /*实现定义*/
static constexpr fmtflags showbase   = /*实现定义*/
static constexpr fmtflags showpoint  = /*实现定义*/
static constexpr fmtflags showpos    = /*实现定义*/
static constexpr fmtflags skipws     = /*实现定义*/
static constexpr fmtflags unitbuf    = /*实现定义*/
static constexpr fmtflags uppercase  = /*实现定义*/
```

常量	解释
- dec	对整数 I/O 使用十进制基数：参见 std::dec
- oct	对整数 I/O 使用八进制基数：参见 std::oct
- hex	 对整数 I/O 使用十六进制基数：参见 std::hex
- basefield	dec | oct | hex。用于掩码操作
------------------------------------------------------------------
- left	    左对齐（向右添加填充字符）：参见 std::left
- right	    右对齐（向左添加填充字符）：参见 std::right
- internal	内部对齐（向内部指定点添加填充字符）：参见 std::internal
- adjustfield	left | right | internal。用于掩码操作
------------------------------------------------------------------
- scientific	使用科学计数法生成浮点类型，如果与 fixed 结合使用，则使用十六进制计数法：参见 std::scientific
- fixed       	使用定点计数法生成浮点类型，如果与 scientific 结合使用，则使用十六进制计数法：参见 std::fixed
- floatfield	scientific | fixed。用于掩码操作
------------------------------------------------------------------
- boolalpha	以字母数字格式插入和提取 bool 类型：参见 std::boolalpha
- showbase	生成前缀以指示整数输出的数字基数，货币 I/O 中需要货币指示符：参见 std::showbase
- showpoint	无条件地为浮点数输出生成小数点字符：参见 std::showpoint
- showpos	为非负数输出生成 + 字符：参见 std::showpos
- skipws	在某些输入操作之前跳过前导空格：参见 std::skipws
- unitbuf	在每次输出操作后刷新输出：参见 std::unitbuf
- uppercase	在某些输出操作中，将某些小写字母替换为其大写等效字母：参见 std::uppercase

```cpp
#include <iostream>
 
int main()
{
    const int num = 150;
 
    // using fmtflags as class member constants:
    std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
    std::cout.setf(std::ios_base::showbase);
    std::cout << num << '\n';
 
    // using fmtflags as inherited class member constants:
    std::cout.setf (std::ios::hex, std::ios::basefield);
    std::cout.setf (std::ios::showbase);
    std::cout << num << '\n';
 
    // using fmtflags as object member constants:
    std::cout.setf(std::cout.hex, std::cout.basefield);
    std::cout.setf(std::cout.showbase);
    std::cout << num << '\n';
 
    // using fmtflags as a type:
    std::ios_base::fmtflags ff;
    ff = std::cout.flags();
    ff &= ~std::cout.basefield;   // unset basefield bits
    ff |= std::ios_base::hex;          // set hex
    ff |= std::cout.showbase;     // set showbase
    std::cout.flags(ff);
    std::cout << num << '\n';
 
    // not using fmtflags, but using manipulators:
    std::cout << std::hex << std::showbase << num << '\n';
}
```



#### std::ios_base::openmode
```cpp
typedef /* implementation defined */ openmode;
static constexpr openmode app       = /* implementation defined */;
static constexpr openmode binary    = /* implementation defined */;
static constexpr openmode in        = /* implementation defined */;
static constexpr openmode out       = /* implementation defined */;
static constexpr openmode trunc     = /* implementation defined */;
static constexpr openmode ate       = /* implementation defined */;
```
指定可用的文件打开标志。它是一个 位掩码类型，定义了以下常量

常量	解释
- **app**	 每次写入前定位到流的末尾
- **binary** 以二进制模式打开
- **in**	 打开以供读取
- **out**	 打开以供写入
- **trunc**	 打开时丢弃流的内容
- **ate**	 打开后立即定位到流的末尾
```cpp
#include <fstream>
#include <iostream>
#include <string>
 
int main()
{
    const char* fname = "unique_name.txt";
 
    // write to a temporary stream object
    std::fstream(fname, std::ios::out | std::ios::trunc) << "Hi";
 
    std::string s;
    std::fstream(fname, std::ios::in) >> s;
    std::cout << s << '\n';
}
```

#### std::ios_base::iostate
```cpp
typedef /*实现定义*/ iostate;
static constexpr iostate goodbit = 0;
static constexpr iostate badbit  = /* 实现定义 */
static constexpr iostate failbit = /* 实现定义 */
static constexpr iostate eofbit  = /* 实现定义 */
```
指定流状态标志。它是一个 BitmaskType，定义了以下常量

常量	    解释
- **goodbit**	无错误
- **badbit**	不可恢复的流错误
- **failbit**	输入/输出操作失败（格式化或提取错误）
- **eofbit**	关联的输入序列已到达文件末尾


#### std::ios_base::seekdir
指定文件查找方向类型。定义了以下常量

常量	解释
- **beg**	流的起始位置
- **end**	流的末尾
- **cur**	流位置指示器的当前位置

```cpp
#include <iostream>
#include <sstream>
#include <string>
 
int main()
{
    std::istringstream in("Hello, World!");
    std::string word1, word2, word3, word4, word5;
 
    in >> word1;
    in.seekg(0, std::ios_base::beg); // <- rewind
    in >> word2;
    in.seekg(1, std::ios_base::cur); // -> seek from cur pos toward the end
    in >> word3;
    in.seekg(-6, std::ios_base::cur); // <- seek from cur pos (end) toward begin
    in >> word4;
    in.seekg(-6, std::ios_base::end); // <- seek from end toward begin
    in >> word5;
 
    std::cout << "word1 = " << word1 << '\n'
              << "word2 = " << word2 << '\n'
              << "word3 = " << word3 << '\n'
              << "word4 = " << word4 << '\n'
              << "word5 = " << word5 << '\n';
}
```

#### std::ios_base::precision
```cpp
streamsize precision() const;
streamsize precision( streamsize new_precision );
```
管理由 std::num_put::do_put 执行的浮点输出的精度（即生成多少位数字）。
1) 返回当前精度。
2) 将精度设置为给定的值。返回之前的精度。
默认精度，由 std::basic_ios::init 建立，为 6。

```cpp
#include <iostream>
 
int main()
{
    const double d = 12.345678901234;
    std::cout << "The  default precision is "   << std::cout.precision() << "\n\n";
    std::cout << "With default precision d is " << d << '\n';
    std::cout.precision(8);
    std::cout << "With high precision d is "    << d << '\n';
}
```