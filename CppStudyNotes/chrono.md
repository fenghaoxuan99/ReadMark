

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->
<!-- code_chunk_output -->

  - [std::chrono::duration](#stdchronoduration)
  - [std::chrono::duration_cast](#stdchronoduration_cast)
- [字面量](#字面量)
  - [可能的实现](#可能的实现)

<!-- /code_chunk_output -->



#### std::chrono::duration
template<
    class Rep,
    class Period = std::ratio<1>
 ->class duration;
1. 类模板 std::chrono::duration 表示时间间隔。
2. 它由 Rep 类型的计次数和计次周期组成，其中计次周期是一个编译期有理数常量，表示从一个计次到下一个的秒数。
3. 存储于 duration 的数据仅有 Rep 类型的计次数。若 Rep 是浮点数，则 duration 能表示小数的计次数。 Period 被包含为时长类型的一部分，且只在不同时长间转换时使用。

```cpp
#include <iostream>
#include <chrono>
 
constexpr auto year = 31556952ll; // 格里高利历年的平均秒数
 
int main()
{
    using shakes          = std::chrono::duration<int, std::ratio<1, 100000000>>;
    using jiffies         = std::chrono::duration<int, std::centi>;
    using microfortnights = std::chrono::duration<float, std::ratio<14*24*60*60, 1000000>>;
    using nanocenturies   = std::chrono::duration<float, std::ratio<100*year, 1000000000>>;
 
    std::chrono::seconds sec(1);
    std::cout << "1 second is:\n";
 
    // 无精度损失的整数尺度转换：无转型
    std::cout << std::chrono::microseconds(sec).count() << " microseconds\n"
              << shakes(sec).count() << " shakes\n"
              << jiffies(sec).count() << " jiffies\n";
 
    // 有精度损失的整数尺度转换：需要转型
    std::cout << std::chrono::duration_cast<std::chrono::minutes>(sec).count()
              << " minutes\n";
 
    // 浮点尺度转换：无转型
    std::cout << microfortnights(sec).count() << " microfortnights\n"
              << nanocenturies(sec).count() << " nanocenturies\n";
}
```


#### std::chrono::duration_cast
1. template <class ToDuration, class Rep, class Period>
constexpr ToDuration duration_cast(const duration<Rep,Period>& d);
```cpp
#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>
 
void f()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
 
int main()
{
    auto t1 = std::chrono::high_resolution_clock::now();
    f();
    auto t2 = std::chrono::high_resolution_clock::now();
 
    // 整数时长：要求 duration_cast
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
 
    // 小数时长：不要求 duration_cast
    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
 
    std::cout << "f() took " << fp_ms.count() << " ms, "
              << "or " << int_ms.count() << " whole milliseconds\n";
}
```


### 字面量
定义于内联命名空间 std::literals::chrono_literals
|字面量|std::literals::chrono_literals|
|:--:|--|
|operator""h   |表示小时的 std::chrono::duration 字面量|
|operator""min |表示分钟的 std::chrono::duration 字面量|
|operator""s   |表示秒的 std::chrono::duration 字面量  |
|operator""ms  |表示毫秒的 std::chrono::duration 字面量|
|operator""us  |表示微秒的 std::chrono::duration 字面量|
|operator""ns  |表示纳秒的 std::chrono::duration 字面量|
#### 可能的实现
```cpp
    constexpr std::chrono::hours operator""h(unsigned long long h)
    {
        return std::chrono::hours(h);
    }

    constexpr std::chrono::minutes operator""min(unsigned long long min)
    {
        return std::chrono::minutes(min);
    }
```

```cpp
#include <iostream>
#include <chrono>
 
int main()
{
    using namespace std::chrono_literals;
    auto day = 24h;
    auto halfhour = 0.5h;
    std::cout << "one day is " << day.count() << " hours\n"
              << "half an hour is " << halfhour.count() << " hours\n";
}
```

#### std::chrono::time_point
template<
    class Clock,
    class Duration = typename Clock::duration
-> class time_point;

```cpp
#include <iostream>
#include <chrono>
#include <ctime>
 
int main()
{
    auto p0 = std::chrono::time_point<std::chrono::system_clock>{};
    auto p1 = std::chrono::system_clock::now();
    auto p2 = p1 - std::chrono::hours(24);
 
    auto epoch_time = std::chrono::system_clock::to_time_t(p0);
    std::cout << "epoch: " << std::ctime(&epoch_time);
    auto today_time = std::chrono::system_clock::to_time_t(p1);
    std::cout << "today: " << std::ctime(&today_time);
 
    std::cout << "hours since epoch: "
              << std::chrono::duration_cast<std::chrono::hours>(
                   p1.time_since_epoch()).count() 
              << '\n';
    std::cout << "yesterday, hours since epoch: "
              << std::chrono::duration_cast<std::chrono::hours>(
                   p2.time_since_epoch()).count() 
              << '\n';
}
```


#### std::chrono::time_point<Clock,Duration>::time_since_epoch

std::chrono::time_point<Clock, Duration>::time_since_epoch 是 std::chrono 库中 time_point 类模板的一个成员函数，
它返回一个表示从时钟的纪元（epoch）到时间点的持续时间间隔的 Duration 类型对象。


#### std::strftime
std::size_t strftime( char* str, std::size_t count, const char* format, const std::tm* time );

```cpp
#include <ctime>
#include <iostream>
#include <locale>
 
int main()
{
    std::locale::global(std::locale("ja_JP.utf8"));
    std::time_t t = std::time(NULL);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t))) {
        std::cout << mbstr << '\n';
    }
}
```