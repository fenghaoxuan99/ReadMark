#include <iostream>

void modifyPointer(int *ptr)
{
    *ptr = 100;    // ✅ 可以修改指针指向的值（影响实参）
    ptr = nullptr; // ❌ 不能改变实参指针的指向（形参是拷贝）
}

int main()
{
    int x = 10;
    int *p = &x;

    std::cout << "Before: *p = " << *p << std::endl; // 输出 10
    modifyPointer(p);
    std::cout << "After: *p = " << *p << std::endl;                            // 输出 100（值被修改）
    std::cout << "p is " << (p == nullptr ? "null" : "not null") << std::endl; // 输出 not null（指向未变）
}
