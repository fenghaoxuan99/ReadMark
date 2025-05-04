#include <memory> // 包含 allocator
#include <vector>

int main()
{
    std::allocator<int> alloc; // 创建一个 int 类型的分配器

    // 分配内存（可以存储 5 个 int）
    int *p = alloc.allocate(5);

    // 构造对象
    alloc.construct(p, 42);      // p[0] = 42
    alloc.construct(p + 1, 100); // p[1] = 100

    // 销毁对象（调用析构函数）
    alloc.destroy(p);
    alloc.destroy(p + 1);

    // 释放内存
    alloc.deallocate(p, 5);

    return 0;
}
