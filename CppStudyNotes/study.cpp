#include <iostream>
#include <typeinfo>
using namespace std;

class A
{
public:
    virtual ~A();
};

using namespace std; 
int main()
{
    A *a = NULL;
    try
    {
        cout << typeid(*a).name() << endl; // Error condition
    }
    catch (bad_typeid)
    {
        cout << "Object is NULL" << endl;
    }
    return 0;
}