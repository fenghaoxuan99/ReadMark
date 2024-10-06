#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<typename... Args>
void FormatPrint(Args... args)
{
    (std::cout << ... << (std::cout << "[" << args, "]")) << std::endl;
}

int main(void)
{
   FormatPrint(1, 2, 3, 4);
   FormatPrint("good", 2, "hello", 4, 110);
   return 0;
}