#include <cassert>
#include <forward_list>

int main()
{
    using F = std::forward_list<int>;

    // Demonstrate the meaning of open range (first, last)
    // in overload (5): the first element of l1 is not moved.
    F l1 = {1, 2, 3, 4, 5};
    F l2 = {10, 11, 12};

    l2.splice_after(l2.cbegin(), l1, l1.cbegin(), l1.cend());
    // Not equivalent to l2.splice_after(l2.cbegin(), l1);
    // which is equivalent to
    // l2.splice_after(l2.cbegin(), l1, l1.cbefore_begin(), l1.end());

    assert((l1 == F{1}));
    assert((l2 == F{10, 2, 3, 4, 5, 11, 12}));

    // Overload (1)
    F x = {1, 2, 3, 4, 5};
    F y = {10, 11, 12};
    x.splice_after(x.cbegin(), y);
    assert((x == F{1, 10, 11, 12, 2, 3, 4, 5}));
    assert((y == F{}));

    // Overload (3)
    x = {1, 2, 3, 4, 5};
    y = {10, 11, 12};
    x.splice_after(x.cbegin(), y, y.cbegin());
    assert((x == F{1, 11, 2, 3, 4, 5}));
    assert((y == F{10, 12}));

    // Overload (5)
    x = {1, 2, 3, 4, 5};
    y = {10, 11, 12};
    x.splice_after(x.cbegin(), y, y.cbegin(), y.cend());
    assert((x == F{1, 11, 12, 2, 3, 4, 5}));
    assert((y == F{10}));
}