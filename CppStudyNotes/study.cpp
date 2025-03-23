#include <iostream>
#include <bitset>

int main()
{
    std::bitset<4> b("1010");                  // 二进制 1010 → 十进制 10
    b.set(0);                                  // 变为 1011（11）
    b.flip(2);                                 // 变为 1111（15）
    std::cout << "Bitset: " << b << "\n";      // 输出 1111
    std::cout << "Count: " << b.all() << "\n"; // 4
    return 0;
}