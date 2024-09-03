


## C语言文件操作
函数 fopen（）将一个文件和一个流关联起来，并初始化一个类型为 FILE 的对象，该对象包含了控制该流的所有信息。这些信息包括指向缓冲区的指针；文件位置指示器，它指定了获取文件的位置；以及指示错误和文件结尾情况的标志。
每个用于打开文件的函数（也就是 fopen（）、freopen（）和 tmpfile（））都会返回一个指向 FILE 对象的指针，该 FILE 对象包含与被打开文件相关联的流。一旦打开了文件，就可以调用函数传递数据并对流进行处理。这些函数都把指向 FILE 对象的指针（通常称为 FILE 指针）作为它们的参数之一。FILE 指针指定了正在进行操作的流

```cpp
FILE *fopen( const char * restrict filename,const char * restrict mode );
FILE *freopen(const char * restrict filename,
                  const char * restrict mode,
                  FILE * restrict stream );
FILE *tmpfile( void );


#include <stdio.h>
#include <stdbool.h>
_Bool isReadWriteable( const char *filename )
{
  FILE *fp = fopen( filename, "r+" );   // 打开一个文件以用于读写
  if ( fp != NULL )                             // fopen()是否执行成功
  {
    fclose(fp);                                 // 成功：关闭文件，没有错误需要处理
    return true;
  }
  else                                          // 失败
    return false;
}
```

## C++文件操作
C++的IO类中定义了三个文件读写流fstream、ifstream以及ofstream，它们都继承于相同的父类istream，通过不同的实现以实现不同的文件流操作。
三者的区别为：
- ifstream：从文件读取数据
- ofstream：从文件写入数据
- fstream：既可以读数据、又可以写数据

|函数名	|用途|
|--|--|
|open(s, mode)	    |以mode模式打开文件s|
|close()	        |关闭文件流|
|is_open()	        |返回文件是否已经打开|
|read(buff, size)	|读入最多size字节数据到buff中|
|write(buff, size)	|写入size字节数据到文件中|

### void open(const char* filename,int mode,int access);
access 打开文件的属性取值是：
0：普通文件，打开访问
1：只读文件
2：隐含文件
4：系统文件

|模式|说明|
|--|--|
|ios::in	|以读方式打开|
|ios::out	|以写方式打开|
|ios::app	|以追加写方式打开|
|ios::trunc	|以截断方式打开文件|
|ios:binary	|以二进制方式打开文件|
|ios::ate	|打开文件后指针定位到文件尾|
|ios::nocreate 　|不建立文件，所以文件不存在时打开失败|
|ios::noreplace　|不覆盖文件，所以打开文件时如果文件存在失败|

这些模式可以单独使用，也可以组合使用，如果需要组合使用，使用逻辑操作符|或起来即可。这里要特别注意的是ios::out模式默认会截断文件，也就是说，ios::out和ios::out | ios::trunc效果是一样的，都会将文件截断。如果不希望以截断方式打开文件时，则需要设置读写模式为ios::out | ios::app，以这种模式打开文件后，数据会以追加的方式写入到文件。

```cpp
写文件

// 写文件
void write_file() {
  ofstream output;
  // 待写入数据
  string output_data = "HelloWorld\nWelcome To Tencent\n";
  // 打开文件
  output.open("test.txt", ios::out);
  // 写入数据
  output.write(output_data.c_str(), output_data.size());
  // 关闭文件
  output.close();
}

读文件
void read_file() {
  ifstream input;
  char input_data[1024];
  // 打开文件
  input.open("test.txt", ios::in);
  // 读取数据
  input.read(input_data, 1024);
  // 打印读取到的数据
  cout << input_data;
  // 关闭文件
  input.close();
}
```

三个IO操作类都继承于istream，可以直接使用IO操作符（<<和>>）来进行文件读写。
```cpp
ofstream output("test.txt");
ifstream input("test.txt");
std::string input_data;
 
output << "HelloWorld\n";
output.close();
 
input >> input_data;
cout << input_data;
input.close();
 
return 0;
```
注意：在使用IO操作符从文件读取数据的时候，数据输入的对象可以是字符串，也可以是对应的数据类型（如int）。如果输入到字符串，默认是读到空白字符的时候就停止了，需要通过循环控制读取后面的数据。

### 流状态
流在执行IO操作的时候，会根据不同的情况产生不同的状态码，如：

|状态位	|说明|
|--|--|
|strm::badbit	|流已崩溃|
|strm::failgit	|IO已崩溃|
|strm::eofbit	|已经读到文件尾|
|strm::goodbit	|一切正常，没有异常|
我们可以使用已经封装好的函数bad()/fail()/eof()/good()来判断当前IO是否已经达到某种状态，如判断文件是否已经读到结束。同时，我们还可以使用clear()函数来清除当前IO对象的状态位，当流已崩溃（如将流中的字符串对象读到一个int对象上）时，可以手动来清除状态位继续往下读取。

示例，使用eof标志位判断文件是否读完成
```cpp
ofstream output("test.txt");
ifstream input("test.txt");
std::string input_data;
 
output << "Hello World\n";
output.close();
 
while (!input.eof()) {  // 没有读到文件尾就一直读取
  input_data.clear();
 
  input >> input_data;  // 读到空白符就停止
  // 过滤掉空行
  if (input_data == "") continue;
  cout << input_data << endl;
}
input.close();
```
因为使用IO操作符从流中读取数据默认遇到空行就停止，所以Hello World\n字符串需要读三次才能读完，第一次是Hello，第二次是World，第三次是换行后的空行.

## getline
流对象中内置了getline()成员方法可以一次读一行数据到字符串数组中，需要传入一个字符数组和最大长度size：
```cpp
ifstream input("test.txt", ios::in);
char buff[1024];
while (!input.eof()) {
  input.getline(buff, 1024)
  cout << buff << endl;
}
```
这个成员方法可以实现一次读一行的操作，但是只支持C风格的字符串传入，无法支持C++中的string类型。这里可以使用系统库的getline()函数来实现，系统库中有一个getline()函数可以直接从IO流中读取一行数据到string中：
```cpp
ifstream input("test.txt", ios::in);
std::string input_data;
while (!input.eof()) {
  getline(input, input_data);
  cout << input_data << endl;
}
```

ifstream &get(char *buf,int num,char delim=’\n’)；
file2.get(str1,127,’A’); //从文件中读取字符到字符串str1，当遇到字符’A’或读取了127个字符时终止。  


## seekg 和 seekp
seekg()是对输入流的操作 g是get缩写
seekp()是对输出流的操作 p是put缩写
ostream & seekp (int offset, int mode);
istream & seekg (int offset, int mode);

|ios：：beg：|表示输入流的开始位置|
|ios：：cur：|表示输入流的当前位置|
|ios：：end：|表示输入流的结束位置|
file.seekp(20L, ios::beg);


### 此外，我们还可以得到当前读写指针的具体位置：
ifstream 类和 fstream 类还有 tellg 成员函数，能够返回文件读指针的位置；
ofstream 类和 fstream 类还有 tellp 成员函数，能够返回文件写指针的位置。

这两个成员函数的原型如下：
int tellg();
int tellp();