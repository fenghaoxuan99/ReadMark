


map ,multimap ,set multiset 都是自动排序的，map 是 key-value 键值对，set 是 key 键值。
map 中所有元素都是 pair，pair 中第一个元素是 key（键值），起到索引作用，第二个元素为 value（实值）。所有元素都会根据元素的键值自动排序。
set 中所有元素都是 value（实值），且不允许有重复的值。


# std::multiset

std::multiset 是一个关联容器，它包含 Key 类型对象的已排序集合。与 set 不同，允许使用等效值的多个键。排序使用键比较函数 Compare 完成。搜索、插入和删除操作具有对数复杂度。

```cpp
template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
> class multiset;
```


#### std::multiset<Key,Compare,Allocator>::insert
```cpp
iterator insert( const value_type& value );

iterator insert( value_type&& value );

iterator insert( iterator pos, const value_type& value );

iterator insert( const_iterator pos, const value_type& value );

iterator insert( const_iterator pos, value_type&& value );

template< class InputIt >
void insert( InputIt first, InputIt last );

void insert( std::initializer_list<value_type> ilist );

iterator insert( node_type&& nh );

iterator insert( const_iterator pos, node_type&& nh );
```

#### std::multiset<Key,Compare,Allocator>::emplace
```cpp
template< class... Args >
iterator emplace( Args&&... args );
```

#### std::multiset<Key,Compare,Allocator>::emplace_hint
```cpp
iterator emplace_hint( const_iterator pos, Args&&... args );
```

#### std::multiset<Key,Compare,Allocator>::extract
```cpp
node_type extract( const_iterator pos );

```cpp
#include <algorithm>
#include <iostream>
#include <string_view>
#include <set>
 
void print(std::string_view comment, const auto& data)
{
    std::cout << comment;
    for (auto datum : data)
        std::cout << ' ' << datum;
 
    std::cout << '\n';
}
 
int main()
{
    std::multiset<int> cont{1, 2, 3};
 
    print("Start:", cont);
 
    // Extract node handle and change key
    auto nh = cont.extract(1);
    nh.value() = 4;
 
    print("After extract and before insert:", cont);
 
    // Insert node handle back
    cont.insert(std::move(nh));
 
    print("End:", cont);
}
```


#### std::multiset<Key,Compare,Allocator>::count
```cpp
size_type count( const Key& key ) const;

template< class K >
size_type count( const K& x ) const;
```
 返回键为 key 的元素数量。

#### std::multiset<Key,Compare,Allocator>::find
```cpp
 C++ 容器库 std::multiset 
iterator find( const Key& key );

const_iterator find( const Key& key ) const;

template< class K >
iterator find( const K& x );

template< class K >
const_iterator find( const K& x ) const;
```