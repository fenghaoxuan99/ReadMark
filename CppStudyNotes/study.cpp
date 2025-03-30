

#include <iostream>

class MyClass
{
public:
    MyClass(int x, int y) : x(x), y(y) {};
    MyClass(const MyClass &other) : x(other.x), y(other.y) {};
    MyClass(MyClass &&other) : x(other.x), y(other.y) {};

    MyClass &operator=(const MyClass &other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    ~MyClass() { std::cout << "Destructor" << std::endl; };
    int x;
    int y;

    void print() const { std::cout << "x: " << x << " y: " << y << std::endl; }

private:
};

int main()
{
    MyClass a{1, 2};
    a.print();

    MyClass b(a);
    b.print();

    MyClass c(std::move(a));
    c.print();

    return 0;
}