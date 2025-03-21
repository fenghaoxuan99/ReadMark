

map ,multimap ,set multiset 都是自动排序的，map 是 key-value 键值对，set 是 key 键值。
map 中所有元素都是 pair，pair 中第一个元素是 key（键值），起到索引作用，第二个元素为 value（实值）。所有元素都会根据元素的键值自动排序。
set 中所有元素都是 value（实值），且不允许有重复的值。

# map
```cpp
template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>

> class map;
```
std::map 是一个 **已排序的关联容器，** 含有键-值对，其中键是唯一的。键通过使用比较函数 Compare 排序。搜索、移除和插入操作具有对数复杂度。Map 通常实现为 红黑树。

std::map 的迭代器以键的升序迭代，其中升序是由构造时使用的比较定义的。

- map內部的实现自建一颗==红黑树==，这颗树具有对数据自动排序的功能,在map内部所有的数据都是有序的.
- unordered_map: unordered_map内部实现了一个哈希表（也叫散列表，通过把关键码值映射到Hash表中一个位置来访问记录，查找的时间复杂度可达到O(1)因此，其元素的排列顺序是无序的。


!!!bote：
**value_type	std::pair<const Key, T>**

```cpp
map<string,int>m;//定义一个map对象m

1：使用insert添加元素
m.insert(pair<string,int>("sd",19));
m.insert(make_pair(string("def"), 2));

2:直接使用数组下标
m["sd"]=19;

3:用insert函数插入value_type数据：
map<int,string> my_map;
my_map.insert(map<int,string>::value_type(1,"first"));
my_map.insert(map<int,string>::value_type(2,"second"));
 
map<int,string>::iterator it;           //迭代器遍历
for(it=my_map.begin();it!=my_map.end();it++)
    cout<<it->first<<it->second<<endl;

```

##### std::map<Key,T,Compare,Allocator>::insert_or_assign
```cpp
template< class M >
std::pair<iterator, bool> insert_or_assign( const Key& k, M&& obj );

template< class M >
std::pair<iterator, bool> insert_or_assign( Key&& k, M&& obj );

template< class M >
iterator insert_or_assign( const_iterator hint, const Key& k, M&& obj );

template< class M >
iterator insert_or_assign( const_iterator hint, Key&& k, M&& obj );
```


k	-	用于查找和插入（如果未找到）的键
hint	-	指示新元素将要插入位置之前的迭代器
obj	-	要插入或赋值的值
```cpp
#include <iostream>
#include <string>
#include <map>
 
void print_node(const auto& node)
{
    std::cout << '[' << node.first << "] = " << node.second << '\n';
}
 
void print_result(auto const& pair)
{
    std::cout << (pair.second ? "inserted: " : "assigned: ");
    print_node(*pair.first);
}
 
int main()
{
    std::map<std::string, std::string> myMap;
 
    print_result(myMap.insert_or_assign("a", "apple"));
    print_result(myMap.insert_or_assign("b", "banana"));
    print_result(myMap.insert_or_assign("c", "cherry"));
    print_result(myMap.insert_or_assign("c", "clementine"));
 
    for (const auto& node : myMap)
        print_node(node);
}
```


##### std::map<Key,T,Compare,Allocator>::emplace
```cpp
template< class... Args >
std::pair<iterator, bool> emplace( Args&&... args );
```
#### std::map<Key,T,Compare,Allocator>::emplace_hint

#### std::map<Key,T,Compare,Allocator>::try_emplace
```cpp
template< class... Args >
std::pair<iterator, bool> try_emplace( const Key& k, Args&&... args );

template< class... Args >
iterator try_emplace( const_iterator hint, const Key& k, Args&&... args );
```
如果容器中已存在等价于 k 的键，则不执行任何操作。否则，将一个新元素插入到容器中，键为 k，值使用 args 构造。在这种情况下，返回值的 bool 部分为 true，否则为 false。


#### std::map<Key,T,Compare,Allocator>::extract

#### std::map<Key,T,Compare,Allocator>::find
```cpp
iterator find( const Key& key );
const_iterator find( const Key& key ) const;

template< class K >
iterator find( const K& x );

template< class K >
const_iterator find( const K& x ) const;
```

#### std::map<Key,T,Compare,Allocator>::erase
从容器移除指定的元素。
```cpp
iterator erase( iterator pos );

iterator erase( const_iterator pos );

iterator erase( iterator first, iterator last );

iterator erase( const_iterator first, const_iterator last );

size_type erase( const Key& key );

template< class K >
size_type erase( K&& x );

```


#### std::map<Key,T,Compare,Allocator>::count
返回键与指定参数等价的元素数量
```cpp
size_type count( const Key& key ) const;

template< class K >
size_type count( const K& x ) const;
```