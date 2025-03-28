
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

  - [string 的基本概念](#string-的基本概念)
  - [string 的赋值操作](#string-的赋值操作)
  - [string 的字符串拼接操作](#string-的字符串拼接操作)
  - [string 的查找和替换](#string-的查找和替换)
  - [string 的字符获取操作](#string-的字符获取操作)
  - [string 的插入和删除操作](#string-的插入和删除操作)
  - [string的大小和容量](#string的大小和容量)

<!-- /code_chunk_output -->


# string 的基本概念
**string 是 c++ 的字符串，本质是一个类,是一个封装容器！**
char* 是一个指针，而 string 是类， 类内封装 char*，管理 char*，使用 string 不用担心字符越界问题，因为这都是类内管理好的了。

|构造函数的原型|功能|
|:--:|--|
|string( )	                |初始化空串|
|string(const char* str)	|将字符串 str 初始化 string 的对象|
|string(const string& str)	|将 str 字符串对象拷贝给 string 的对象,也就是拷贝构造函数|
|string(int n,char c)	    |将 n 个字符 c 拷贝给 string 对象|

## string 的赋值操作
当对象被初始化后，我们也可以给对象重新的赋值一些新的值过去。

|赋值操作的函数原型	|功能|
|:--:|--|
|string& operator=(const char* str)	    |把 char* 类型的字符串赋值给 string 的对象|
|string& operator=(const string& str)	|把字符串 str 赋值给 string 的对象|
|string& operator=(char c)	            |把字符 c 赋值给 string 的对象|
|string& assign(const char *str)	    |把字符串 str 赋给 string 的对象|
|string& assign(const char *s, int n)	|取 字符串 str 中的 n 个字符赋值给 string 的对象|
|string& assign(const string &s)	    |把 str 字符串对象赋值给string 的对象|
|string& assign(int n, char c)	        |把 n 个字符 c 赋值给 string 的对象|


```cpp
	string str4;
	str4.assign("hello c++");//string& assign(const char *str)
	cout << "str4 = " << str4 << endl;

	string str5;
	str5.assign("hello c++",5); //string& assign(const char *s, int n)
	cout << "str5 = " << str5 << endl;

	string str6;
	str6.assign(str5);
	cout << "str6 = " << str6 << endl;

	string str7;
	str7.assign(5, 'x'); //string& assign(int n, char c)
	cout << "str7 = " << str7 << endl;
```

## string 的字符串拼接操作
功能：将字符串追加拼接到自身字符串的尾部

|函数的原型	|功能|
|:--:|--|
|string& opetator+=(const char* str)	|重载+=操作符,将 str 字符串拼接到 string 的对象尾部|
|string& operator+=(const char c)	    |重载+=操作符，将字符c拼接到 string 的对象尾部|
|string& operator+=(const string& str)	|重载+=操作符，将 str字符串拼接到 string 的对象尾部|
|string& append(const char *str)	    |把字符串 str 追加到 string 的对象尾部|
|string& append(const char *str, int n)	|把字符串str的前n个字符追加到string的对象的尾部|
|string& append(const string &str)	    |等价 operator+=(const string& str)|
|string& append(const string &s, int pos, int n)	|字符串 str 从 pos 的位置开始截取 n 个字符追加到stringde 的对象尾部|


## string 的查找和替换
|函数的原型|	功能|
|:--:|--|
|int find(const string& str, int pos = 0) const	|查找str字符串第一次出现的位置，从string的对象中的第0个位置开始查找，找到返回下标，找不到返回-1|
|int find(const char* str, int pos = 0) const	    |同上|
|int find(const char* str, int pos, int n) const	|从pos的位置开始查找前n个str|
|int rfind(const string& str, int pos = npos) const	|查找str最后一次位置,从pos开始查找，返回str的位置是从左边算起|
|int rfind(const char* s, int pos, int n) const	    |从pos查找s的前n个字符最后一次位置|
|int rfind(const char c, int pos = 0) const	        |查找字符c最后一次出现位置|
|string& replace(int pos, int n, const string& str)	|替换从pos开始n个字符为字符串str|
|string& replace(int pos, int n, const char* s)	    |替换从pos开始的n个字符为字符串s|
|string& replace(size_t pos, size_t n, size_t n1, char c);  |将当前字符串从pos索引开始的n个字符，替换成n1个字符c|
|string& replace(iterator i1, iterator i2, const char* s);  |将当前字符串[i1,i2)区间中的字符串替换为字符串s|


find函数是全匹配，rfind是反向匹配。

**寻找等于给定字符序列中字符之一的首个字符。搜索只考虑区间 [pos, size()) 。若区间中不存在字符，则返回 npos 。**

#### size_type find_first_of( const CharT* s, size_type pos, size_type count ) const;
==寻找等于范围 [s, s+count) 中字符中字符之一的首个字符。此范围能包含空字符== 注意这里是寻找范围，而不是字符串。



## string 的字符获取操作
|函数原型	|功能|
|:--:|--|
|char& operator[](int n)	|重载[ ],获取第 n 个索引string 对象的字符|
|char& at(int n)            |同上功能|

### std::basic_string<CharT,Traits,Allocator>::substr
- basic_string substr( size_type pos = 0, size_type count = npos ) const;           (C++20 前)
- constexpr basic_string substr( size_type pos = 0, size_type count = npos ) const; (C++20 起)
 返回子串 [pos, pos+count) 。若请求的子串越过 string 的结尾，或若 count == npos ，则返回的子串为 [pos, size()) 


```cpp
void test01()
{
	string str = "hello world";
	//size函数计算字符大小
	for (int i = 0; i < str.size(); i++)
	{	//char& operator[](int n)
		cout << str[i] << " ";//结果： hello world
	}
	cout << endl;

	for (int i = 0; i < str.size(); i++)
	{	//char& at(int n)
		cout << str.at(i) << " ";//结果： hello world
	}
	cout << endl;


	//字符修改
	str[0] = 'x';
	str.at(1) = 'x';
	cout << str << endl;// 结果：xxllo world
}
```

## string 的插入和删除操作

|函数原型	|功能|
|:--:|--|
|string& insert(int pos, const char* str)	|从pos位置插入字符串str|
|string& insert(int pos, const string& str)	|从pos位置插入字符串str|
|string& insert(int pos, int n, char c)	    |从pos位置插入n字符串c|
|string& erase (int pos, int n = npos)      |从 pos开始删除n个字符|
```cpp
basic_string& insert(size_type pos, const basic_string& str, 
                    size_type subpos, size_type sublen = npos);
```
作用：在位置 pos 前插入 str 的子串，子串从 subpos 开始，长度为 sublen。
参数：

- pos：插入位置。
- str：源字符串。
- subpos：子串起始位置。
- sublen：子串长度（默认为 npos，即到字符串末尾）。




## string的大小和容量
1. size()和length()：返回string对象的字符个数，他们执行效果相同。
2. max_size()：返回string对象最多包含的字符数，超出会抛出length_error异常
3. capacity()：重新分配内存之前，string对象能包含的最大字符数

## 类型转换处理
### 转为string类型

1. to_string()：将其他类型转换为string类型
2. 通过 ostringstream 转换
```cpp 
    int num = 123;
    std::ostringstream ss;
    ss << num;
    ss.str();
```    
### 转为int类型
1.  std::string str = "668";
    int num = 0;
 	sscanf(str.c_str(), "%d", &num);
2. 通过 istringstream 转换
    std::string str = "668";
    int num = 0;
    std::istringstream ss(str);
    ss >> num;

c_str()：生成一个const char*指针，指向以空字符终止的数组。
strcpy(c,s.c_str());将数据进行拷贝。


std::stoi, std::stol, std::stoll
std::stoul, std::stoull
===
1. int       stoi( const std::string& str, std::size_t* pos = 0, int base = 10 );
2. int       stoi( const std::wstring& str, std::size_t* pos = 0, int base = 10 );

long      stol( const std::string& str, std::size_t* pos = 0, int base = 10 );
long      stol( const std::wstring& str, std::size_t* pos = 0, int base = 10 );

long long stoll( const std::string& str, std::size_t* pos = 0, int base = 10 );
long long stoll( const std::wstring& str, std::size_t* pos = 0, int base = 10 );

若 pos 不是空指针，则指针 ptr ——转换函数内部者——将接收 str.c_str() 中首个未转换字符的地址，将计算该字符的下标并存储之于 *pos ，该对象给出转换所处理的字符数。
str	-	要转换的字符串
pos	-	存储已处理字符数的整数的地址
bas -	数的底数，默认为 10



#### copy函数
size_type copy( CharT* dest, size_type count, size_type pos = 0 ) const;
constexpr size_type copy( CharT* dest, size_type count, size_type pos = 0 ) const;
复制子串 [pos, pos+count) 到 dest 所指向的字符串。若请求的子串越过 string 结尾，或若 count == npos ，则复制的子串为 [pos, size()) 。产生的字符串不是空终止的。

若 pos > size() ，则抛出 std::out_of_range 。


#### std::hash (std::string)
  std::cout << std::hash<std::string>{}(s) << '\n';

