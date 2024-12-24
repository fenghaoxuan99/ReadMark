/***
 * @Author: feng 1804831168@qq.com
 * @Date: 2024-12-24 19:11:14
 * @LastEditors: feng 1804831168@qq.com
 * @LastEditTime: 2024-12-24 19:11:55
 * @Description:
 * @Copyright (c) 2024 by Feng, All Rights Reserved.
 */
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

int main()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    std::cout << "24 hours ago, the time was "
              << std::put_time(std::localtime(&now_c), "%F %T") << '\n';

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::cout << "Hello World\n";
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Printing took "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << "us.\n";
}