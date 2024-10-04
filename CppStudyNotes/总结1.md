

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

  - [宏定义 #define 在编译期间将宏展开，并替换宏定义中的代码。](#宏定义-define-在编译期间将宏展开并替换宏定义中的代码)
  - [与宏定义不同，typedef 是在编译阶段处理的，有更严格的类型检查。](#与宏定义不同typedef-是在编译阶段处理的有更严格的类型检查)
  - [sizeof计算大小的小技巧](#sizeof计算大小的小技巧)
  - [几种类型转换](#几种类型转换)
  - [浅拷贝（Shallow Copy）](#浅拷贝shallow-copy)
  - [深拷贝（Deep Copy）](#深拷贝deep-copy)
  - [C++ 的多态必须满足两个条件：](#c-的多态必须满足两个条件)
- [字节对齐](#字节对齐)
  - [区分指针类型和数组类型](#区分指针类型和数组类型)
  - [new和delete是如何实现的](#new和delete是如何实现的)
  - [被free回收的内存是立即返还给操作系统吗？](#被free回收的内存是立即返还给操作系统吗)
  - [C++中struct和class的区别](#c中struct和class的区别)
  - [C++中const和static的作用](#c中const和static的作用)
  - [C++调用C函数：](#c调用c函数)
  - [C调用C++函数](#c调用c函数-1)
  - [构造函数](#构造函数)

<!-- /code_chunk_output -->


## 宏定义 #define 在编译期间将宏展开，并替换宏定义中的代码。

预处理器只进行简单的文本替换，不涉及类型检查。
比如：
#define INT_VECTOR std::vector<int>
typedef 是一种类型定义关键字，用于为现有类型创建新的名称（别名）。

## 与宏定义不同，typedef 是在编译阶段处理的，有更严格的类型检查。
typedef std::vector<int> IntVector;


## sizeof计算大小的小技巧
- 指针的大小永远是固定的，取决于处理器位数，32位就是 4 字节，64位就是 8 字节
- 数组作为函数参数时会退化为指针，大小要按指针的计算
- struct 结构体要考虑字节对齐
- 字符串数组要算上末尾的 '\0'


## 几种类型转换
- static_cast       静态转换，用于基本类型之间的转换，不涉及到类和结构体之间的转换
- const_cast        常量转换，用于去掉或增加 const 或 volatile 修饰符
- reinterpret_cast  重新解释转换，用于不同类型指针之间的转换，也可以用于基本类型和类之间的转换
- dynamic_cast      动态转换，用于类之间的转换，需要进行运行时检查，只有在运行时才能确定转换是否成功


## 不同拷贝类型
### 浅拷贝（Shallow Copy）
浅拷贝是一种简单的拷贝方式，它仅复制对象的基本类型成员和指针成员的值，而不复制指针所指向的内存。
这==可能导致两个对象共享相同的资源，从而引发潜在的问题，如内存泄漏、意外修改共享资源等==。
一般来说编译器默认帮我们实现的拷贝构造函数就是一种浅拷贝。
POD(plain old data) 类型的数据就适合浅拷贝。
简单来说，浅拷贝也可以理解为直接按 bit 位复制，基本等价于 memcpy()函数。

### 深拷贝（Deep Copy）
深拷贝不仅复制对象的基本类型成员和指针成员的值，还复制指针所指向的内存。
因此，两个对象不会共享相同的资源，避免了潜在问题。
深拷贝通常需要显式实现拷贝构造函数和赋值运算符重载。

```cpp
#include <iostream>
#include <cstring>

class MyClass {
public:
    MyClass(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // 深拷贝的拷贝构造函数
    MyClass(const MyClass& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // 深拷贝的赋值运算符重载
    MyClass& operator=(const MyClass& other) {
        if (this == &other) {
            return *this;
        }
        
        delete[] data;
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
        
        return *this;
    }
    
   void SetString(const char* str) {
     if (data != NULL) {
       delete[] data;
     }
     data = new char[strlen(str) + 1];
     strcpy(data, str);
   }
   
    ~MyClass() {
        delete[] data;
    }

    void print() {
        std::cout << data << std::endl;
    }

private:
    char* data;
};

int main() {
    MyClass obj1("Hello, World!");
    MyClass obj2 = obj1; // 深拷贝

    obj1.print(); // 输出：Hello, World!
    obj2.print(); // 输出：Hello, World!

    // 修改obj2中的数据，不会影响obj1
    obj1.SetString("Test");
    obj2.print(); // 输出：Hello, World!
    return 0;
}
```

## C++ 的多态必须满足两个条件：
- 必须通过基类的指针或者引用调用虚函数
- 被调用的函数是虚函数，且必须完成对基类虚函数的重写


# 字节对齐 
```cpp
#if defined(__GNUC__) || defined(__GNUG__)
  #define ONEBYTE_ALIGN __attribute__((packed))
#elif defined(_MSC_VER)
  #define ONEBYTE_ALIGN
  #pragma pack(push,1)
#endif

struct Info {
  uint8_t a;
  uint32_t b;
  uint8_t c;
} ONEBYTE_ALIGN;

#if defined(__GNUC__) || defined(__GNUG__)
  #undef ONEBYTE_ALIGN
#elif defined(_MSC_VER)
  #pragma pack(pop)
  #undef ONEBYTE_ALIGN
#endif

std::cout << sizeof(Info) << std::endl;   // 6 1 + 4 + 1
std::cout << alignof(Info) << std::endl;  // 1
```

## 区分指针类型和数组类型
int *p[10]   表示指针数组，强调数组概念，是一个数组变量，数组大小为10，数组内每个元素都是指向int类型的指针变量。
int (*p)[10] 表示数组指针，强调是指针，只有一个变量，是指针类型，不过指向的是一个int类型的数组，这个数组大小是10。
int *p(int)  是函数声明，函数名是p，参数是int类型的，返回值是int *类型的。
int (*p)(int)是函数指针，强调是指针，该指针指向的函数具有int类型参数，并且返回值是int类型的。

## new和delete是如何实现的
new的实现过程是：首先调用名为operator new的标准库函数，分配足够大的原始为类型化的内存，以保存指定类型的一个对象；接下来运行该类型的一个构造函数，用指定初始化构造对象；最后返回指向新分配并构造后的的对象的指针
delete的实现过程：对指针指向的对象运行适当的析构函数；然后通过调用名为operator delete的标准库函数释放该对象所用内存

## 被free回收的内存是立即返还给操作系统吗？
不是的，被free回收的内存会首先被ptmalloc使用双链表保存起来，当用户下一次申请内存的时候，会尝试从这些内存中寻找合适的返回。这样就避免了频繁的系统调用，占用过多的系统资源。同时ptmalloc也会尝试对小块内存进行合并，避免过多的内存碎片。

## C++中struct和class的区别
- 相同点
1. 两者都拥有成员函数、公有和私有部分
2. 任何可以使用class完成的工作，同样可以使用struct完成
- 不同点
1. 两者中如果不对成员不指定公私有，struct默认是公有的，class则默认是私有的
2. class默认是private继承， 而struct默认是public继承

## C++中const和static的作用
1. static
 - 不考虑类的情况
隐藏。所有不加static的全局变量和函数具有全局可见性，可以在其他文件中使用，加了之后只能在该文件所在的编译模块中使用
默认初始化为0，包括未初始化的全局静态变量与局部静态变量，都存在全局未初始化区
静态变量在函数内定义，始终存在，且只进行一次初始化，具有记忆性，其作用范围与局部变量相同，函数退出后仍然存在，但不能使用
 - 考虑类的情况
static成员变量：只与类关联，不与类的对象关联。定义时要分配空间，不能在类声明中初始化，必须在类定义体外部初始化，初始化时不需要标示为static；可以被非static成员函数任意访问。
static成员函数：不具有this指针，无法访问类对象的非static成员变量和非static成员函数；不能被声明为const、虚函数和volatile；可以被非static成员函数任意访问

2. const
- 不考虑类的情况
const常量在定义时必须初始化，之后无法更改
const形参可以接收const和非const类型的实参，例如// i 可以是 int 型或者 const int 型void fun(const int& i){ //...}
- 考虑类的情况
const成员变量：不能在类定义外部初始化，只能通过构造函数初始化列表进行初始化，并且必须有构造函数；不同类对其const数据成员的值可以不同，所以不能在类中声明时初始化
const成员函数：const对象不可以调用非const成员函数；非const对象都可以调用；不可以改变非mutable（用该关键字声明的变量可以在const成员函数中被修改）数据的值
补充一点const相关：const修饰变量是也与static有一样的隐藏作用。只能在该文件中使用，其他文件不可以引用声明使用。 因此在头文件中声明const变量是没问题的，因为即使被多个文件包含，链接性都是内部的，不会出现符号冲突。


## C++调用C函数：
```cpp
//xx.h
extern int add(...)

//xx.c
int add(){
    
}

//xx.cpp
extern "C" {
    #include "xx.h"
}
```

## C调用C++函数
```cpp
//xx.h
extern "C"{
    int add();
}
//xx.cpp
int add(){    
}
//xx.c
extern int add();
```

## 构造函数
- 默认构造函数
- 初始化构造函数（有参数）
- 拷贝构造函数
- 移动构造函数（move和右值引用）
- 委托构造函数
- 转换构造函数
```cpp
#include <iostream>
using namespace std;

class Student{
public:
    Student(){//默认构造函数，没有参数
        this->age = 20;
        this->num = 1000;
    };  
    Student(int a, int n):age(a), num(n){}; //初始化构造函数，有参数和参数列表
    Student(const Student& s){              //拷贝构造函数，这里与编译器生成的一致
        this->age = s.age;
        this->num = s.num;
    }; 
    Student(int r){                //转换构造函数,形参是其他类型变量，且只有一个形参
        this->age = r;
		this->num = 1002;
    };
    ~Student(){}
public:
    int age;
    int num;
};

int main(){
    Student s1;
    Student s2(18,1001);
    int a = 10;
    Student s3(a);
    Student s4(s3);
    
    printf("s1 age:%d, num:%d\n", s1.age, s1.num);
    printf("s2 age:%d, num:%d\n", s2.age, s2.num);
    printf("s3 age:%d, num:%d\n", s3.age, s3.num);
    printf("s2 age:%d, num:%d\n", s4.age, s4.num);
    return 0;
}
//运行结果
//s1 age:20, num:1000
//s2 age:18, num:1001
//s3 age:10, num:1002
//s2 age:10, num:1002
```


## public，protected和private访问和继承权限/public/protected/private的区别？
- public的变量和函数在类的内部外部都可以访问。
- protected的变量和函数只能在类的内部和其派生类中访问。
- private修饰的元素只能在类内访问。

### 访问权限
派生类可以继承基类中除了构造/析构、赋值运算符重载函数之外的成员，但是这些成员的访问属性在派生过程中也是可以调整的，三种派生方式的访问权限如下表所示：注意外部访问并不是真正的外部访问，而是在通过派生类的对象对基类成员的访问。

==派生类对基类成员的访问形象有如下两种==
- 内部访问：由派生类中新增的成员函数对从基类继承来的成员的访问
- 外部访问：在派生类外部，通过派生类的对象对从基类继承来的成员的访问

### 继承权限
1. public继承
公有继承的特点是基类的公有成员和保护成员作为派生类的成员时，都保持原有的状态，而基类的私有成员任然是私有的，不能被这个派生类的子类所访问.

2. protected继承
保护继承的特点是基类的所有公有成员和保护成员都成为派生类的保护成员，并且只能被它的派生类成员函数或友元函数访问，基类的私有成员仍然是私有的.

3. private继承
私有继承的特点是基类的所有公有成员和保护成员都成为派生类的私有成员，并不被它的派生类的子类所访问，基类的成员只能由自己派生类访问，无法再往下继承.


## 在成员函数中调用delete this会出现什么问题
在类对象的内存空间中，只有数据成员和虚函数表指针，并不包含代码内容，类的成员函数单独放在代码段中。在调用成员函数时，隐含传递一个this指针，让成员函数知道当前是哪个对象在调用它。当调用delete this时，类对象的内存空间被释放。在delete this之后进行的其他任何函数调用，只要不涉及到this指针的内容，都能够正常运行。一旦涉及到this指针，如操作数据成员，调用虚函数等，就会出现不可预期的问题。


