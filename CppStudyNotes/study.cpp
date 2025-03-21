#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <cassert>

int main()
{
         // error: assert does not take two arguments
    assert((std::is_same_v<int, int>));      // OK: one argument
    static_assert(std::is_same_v<int, int>); // OK: not a macro

    
}