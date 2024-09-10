



C++库中，ios，stringstream,ifstream,ofstream,basic_ios等类都有一个公有成员函数rdbuf(), 返回一个指向流缓冲区当前位置的指针， 其中ios类的rdbuf可以接收一个streambuf* 类的指针， 把对象的流和参数关联起来。

streambuf* rdbuf() const; //get
streambuf* rdbuf (streambuf* sb); //set


## 错误用法，会产生两次析构
```cpp
#include <fstream>
#include <iostream>
// wrong revison
int main()
{
    std::ofstream log("oops.log");
    std::cout.rdbuf(log.rdbuf());
    std::cout << "Woo Oops!\n"; //输出到文件log
    return 0;
}

```



## 正确用法 RAII
```cpp
struct buffer_restorer {
    std::ios &m_s;
    std::streambuf *m_buf;

    buffer_restorer(std::ios &s, std::streambuf *buf) : m_s(s), m_buf(buf) {}
    ~buffer_restorer() { m_s.rdbuf(m_buf); }
};

int main()
{
    std::ofstream log("oops.log");
    // std::cout.rdbuf(log.rdbuf()) 返回cout的流对象指针，使cout重定向到log文件中
    buffer_restorer r(std::cout, std::cout.rdbuf(log.rdbuf()));
    std::cout << "Woo Oops!\n";
    return 0;
}
```

## 官网参考代码
```cpp
// redirecting cout's output thrrough its stream buffer
#include <iostream>     // std::streambuf, std::cout
#include <fstream>      // std::ofstream

int main () {
  std::streambuf *psbuf, *backup;
  std::ofstream filestr;
  filestr.open ("test.txt");

  backup = std::cout.rdbuf();     // back up cout's streambuf

  psbuf = filestr.rdbuf();        // get file's streambuf
  std::cout.rdbuf(psbuf);         // assign streambuf to cout

  std::cout << "This is written to the file";

  std::cout.rdbuf(backup);        // restore cout's original streambuf

  filestr.close();

  return 0;
}
```