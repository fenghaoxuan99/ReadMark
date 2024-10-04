#include <iostream>
#include <cstdlib>
 
class Static {
public:
 
    ~Static() 
    {
        std::cout << "Static dtor\n";
    }
};
 
class Local {
public:
    ~Local() 
    {
        std::cout << "Local dtor\n";
    }
};
 
Static static_variable; // *将*调用此对象的析构函数
 
void atexit_handler()
{
    std::cout << "atexit handler\n";
}
 
int main()
{
    
    const int result = std::atexit(atexit_handler); // 将调用处理函数
   static  Local local_variable; // 将*不*调用此对象的析构函数
    if (result != 0) {
        std::cerr << "atexit registration failed\n";
        return EXIT_FAILURE;
    }
 
    std::cout << "test\n";
    std::exit(EXIT_FAILURE);
}