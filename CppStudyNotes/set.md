
# Set容器的基本概念
- 概念：
set 容器 为集合；
- 特点：
set 容器中所有的元素都会在插入时自动被排序。
set 容器中不允许有重复的元素。
**插入数据时候默认按升序排列**

- 说明：
set 和 multiset 的操作基本一致，区别在于，set容器不可以有重复的数据，而multiset可以重复的数据；
即使你插入的数据是无序序列，set容器也会自动帮你排好顺序；
set 容器插入时候没有push_back()的操作，只有insert（）的操作；

std::set **是关联容器**，含有Key类型对象的已排序集。用比较函数 较 (Compare) 进行排序。搜索、移除和插入拥有对数复杂度。 set 通常以红黑树实现。

|函数原型|功能|
|:--:|--|
|insert(elem)	 |在容器中插入elem元素|
|clear()	     |清除所有元素|
|erase(pos)      |删除pos迭代器所指的元素|
|erase(beg, end) |删除区间[beg,end)的所有元素|
|erase(elem)	 |删除容器中值为elem的元素|
```cpp
std::pair<iterator, bool> insert( const value_type& value );
std::pair<iterator, bool> insert( value_type&& value );	(since C++11)
	
iterator insert( iterator pos, const value_type& value );(until C++11)
iterator insert( const_iterator pos, const value_type& value );(since C++11)
iterator insert( const_iterator pos, value_type&& value );	(since C++11)

template< class InputIt >
void insert( InputIt first, InputIt last );

void insert( std::initializer_list<value_type> ilist );(since C++11)
insert_return_type insert( node_type&& nh );(since C++17)
iterator insert( const_iterator pos, node_type&& nh );(since C++17)
```

#### std::set<Key,Compare,Allocator>::emplace
```cpp
template< class... Args >
std::pair<iterator,bool> emplace( Args&&... args );
```
如果容器中没有具有该键的元素，则将使用给定的 args 就地构造的新元素插入到容器中。
新元素的构造函数使用与提供给 emplace 的参数完全相同的参数调用，并通过 std::forward<Args>(args)... 转发。
即使容器中已经存在具有该键的元素，也可能会构造元素，在这种情况下，新构造的元素将立即销毁。

#### std::set<Key,Compare,Allocator>::emplace_hint
```cpp
iterator emplace_hint( const_iterator position, Args&&... args );
```
将新元素插入到容器中，尽可能靠近 hint 前面的位置。
新元素的构造函数使用与提供给 emplace 的参数完全相同的参数调用，并通过 std::forward<Args>(args)... 转发。

hint	-	迭代器，指向新元素将被插入的位置之前的位置
args	-	转发给元素构造函数的参数

|函数|返回值|描述|
|:--:|:--:|:--:|
|emplace	 |pair<iterator, bool>	|bool 表示是否插入成功，iterator 指向插入的元素。|
|emplace_hint|iterator	            |直接返回指向插入元素的迭代器（无论是否是新插入的）。|
**在有序插入场景中（例如构建有序数据集），可以缓存上一次插入的迭代器作为下一次的 hint，显著提升性能。**
示例：按顺序插入 1, 2, 3, ..., N 时，每次插入后更新 hint 为返回的迭代器。

#### std::set<Key,Compare,Allocator>::count
```cpp
size_type count( const Key& key ) const;

template< class K >
size_type count( const K& x ) const;
```
返回键为 key 的元素数量。由于此容器不允许重复键，因此结果为 1 或 0。



#### std::set<Key,Compare,Allocator>::find
```cpp
iterator find( const Key& key );
const_iterator find( const Key& key ) const;
template< class K > iterator find( const K& x );
template< class K > const_iterator find( const K& x ) const;
```
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

#### std::set<Key,Compare,Allocator>::extract
```cpp
node_type extract( const_iterator position );
node_type extract( const Key& k );
```
从容器中提取节点。
是 C++17 引入的高效操作，允许从集合中提取节点（node），以便修改元素或在不同容器间转移元素所有权，无需拷贝或重新分配内存。
##### 核心功能
- 提取节点：将元素从 std::set 中移除，返回一个 node_type 节点句柄。
- 修改元素：通过节点句柄可以修改元素的非键部分（如 std::map 的 value）。
- 转移元素：将节点插入到另一个兼容的容器中（如另一个 std::set）。
节点句柄是移动专属类型（move-only），支持以下操作：

操作	说明
bool empty() const	检查节点句柄是否为空（未包含元素）。
explicit operator bool()	转换为布尔值，判断节点是否有效（等价于 !empty()）。
value_type& value()	访问节点中的元素（需确保节点非空）。

**std::set 的键不可修改，即使通过节点句柄也无法修改键值。**
若需修改键，需使用 std::map，且只能修改 value 部分（键仍不可变）。
```cpp
std::map<int, std::string> m {{1, "a"}, {2, "b"}};
auto node = m.extract(1);
node.value().second = "modified";  // 允许修改 value
m.insert(std::move(node));         // m = { {1, "modified"}, {2, "b"} }
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