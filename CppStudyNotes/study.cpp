#include <iostream>
#include <sstream>

template <class T>
class test
{
public:
    T &operator[](int i)
    {
        return value[i];
    }

private:
    T value[10];
};

int main()
{
    test<test<int>> t;
    for (int i = 0; i < 10; i++)
    {
        t[i][i] = i;
    }
    for (int i = 0; i < 10; i++)
    {
        std::cout << t[i][i] << std::endl;
    }
    return 0;
}