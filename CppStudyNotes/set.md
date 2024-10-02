
# set 和 multiset容器的基本概念
- 概念：
set 容器 为集合；multiset 也是集合；插入数据时候默认按升序排列。

- 说明：
set 和 multiset 的操作基本一致，区别在于，set容器不可以有重复的数据，而multiset可以又重复的数据；
即使你插入的数据是无序序列，set容器也会自动帮你排好顺序；
set 容器插入时候没有push_back()的操作，只有insert（）的操作；

std::set 是关联容器，含有Key类型对象的已排序集。用比较函数 较 (Compare) 进行排序。搜索、移除和插入拥有对数复杂度。 set 通常以红黑树实现。

|函数原型|功能|
|:--:|--|
|insert(elem)	 |在容器中插入elem元素|
|clear()	     |清除所有元素|
|erase(pos)      |删除pos迭代器所指的元素|
|erase(beg, end) |删除区间[beg,end)的所有元素|
|erase(elem)	 |删除容器中值为elem的元素|




#### std::set<Key,Compare,Allocator>::emplace
template< class... Args >
std::pair<iterator,bool> emplace( Args&&... args );
返回pair，若插入成功，则返回pair的second为true，否则为false。
```cpp

```


#### std::set<Key,Compare,Allocator>::find
1. iterator find( const Key& key );
2. const_iterator find( const Key& key ) const;
3. template< class K > iterator find( const K& x );
4. template< class K > const_iterator find( const K& x ) const;

返回值
指向键等于 key 的元素的迭代器。若找不到这种元素，则返回尾后（见 end() ）迭代器。

```cpp
 std::set<int> example = {1, 2, 3, 4};
 
    auto search = example.find(2);
    if (search != example.end()) {
        std::cout << "Found " << (*search) << '\n';
    } else {
        std::cout << "Not found\n";
    }
```


#### std::set<Key,Compare,Allocator>::equal_range
1. std::pair<iterator,iterator> equal_range( const Key& key );
2. std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
3. template< class K >
std::pair<iterator,iterator> equal_range( const K& x );
4. template< class K >
std::pair<const_iterator,const_iterator> equal_range( const K& x ) const;




#### std::set<Key,Compare,Allocator>::lower_bound
1. iterator lower_bound( const Key& key );
2. const_iterator lower_bound( const Key& key ) const;
3. template< class K >
iterator lower_bound(const K& x);
4. template< class K >
const_iterator lower_bound(const K& x) const;

返回指向首个不小于 key 的元素的迭代器。