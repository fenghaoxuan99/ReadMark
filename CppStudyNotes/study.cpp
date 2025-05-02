#include <iostream>
using namespace std;

int main()
{
    int x = 10;
    int &ref1 = x; // 正确：绑定到非常量左值

    const int y = 20;
    int &ref2 = y; // 错误：不能绑定到常量左值

    int &ref3 = 30;    // 错误：不能绑定到右值
    int &ref4 = x + 1; // 错误：不能绑定到临时对象(右值)
    return 0;
}