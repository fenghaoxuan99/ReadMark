#include <csignal>
#include <iostream>
 
void signal_handler(int signal)
{
    std::cout << "Received signal " << signal << '\n';
}
 
int main()
{
    // 安装信号处理函数
    std::signal(SIGTERM, signal_handler);
 
    std::cout << "Sending signal " << SIGTERM << '\n';
    std::raise(SIGTERM);
}