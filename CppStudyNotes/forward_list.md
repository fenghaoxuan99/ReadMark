

# std::forward_list
```cpp
template<
    class T,
    class Allocator = std::allocator<T>

> class forward_list;
```
std::forward_list 是一个容器，支持在容器中任何位置快速插入和移除元素。
不支持快速随机访问。它被实现为单向链表。与 std::list 相比，当不需要双向迭代时，此容器提供更节省空间的存储。

#### std::forward_list<T,Allocator>::insert_after
```cpp
iterator insert_after( const_iterator pos, const T& value );
iterator insert_after( const_iterator pos, T&& value );
iterator insert_after( const_iterator pos, size_type count, const T& value );
template< class InputIt >
iterator insert_after( const_iterator pos, InputIt first, InputIt last );
iterator insert_after( const_iterator pos, std::initializer_list<T> ilist );

```
在容器中指定位置之后插入元素。

##### 参数
pos	-	内容将被插入其后的迭代器
value	-	要插入的元素值
count	-	要插入的副本数量
first, last	-	定义要插入元素的源范围的迭代器对
ilist	-	从中插入值的初始化器列表

#### std::forward_list<T,Allocator>::emplace_after
```cpp
iterator emplace_after( const_iterator pos, Args&&... args );
```
在容器中指定位置之后的位置插入新元素。元素被就地构造，即不执行复制或移动操作。元素的构造函数使用与函数提供的参数完全相同的参数调用。

#### std::forward_list<T,Allocator>::erase_after
```cpp
iterator erase_after( const_iterator pos );
iterator erase_after( const_iterator first, const_iterator last );
```
从容器中删除元素。
pos	-	指向要移除元素之前元素的迭代器
first, last	-	定义要移除元素范围的迭代器对

#### std::forward_list<T,Allocator>::push_front
```cpp
void push_front( const T& value );
void push_front( T&& value );
```
在容器的开头插入元素。
value	-	要插入的元素值

#### std::forward_list<T,Allocator>::emplace_front
```cpp
void emplace_front( Args&&... args );
```
在容器的开头插入新元素。元素被就地构造，即不执行复制或移动操作。元素的构造函数使用与函数提供的参数完全相同的参数调用。

#### std::forward_list<T,Allocator>::pop_front
```cpp
void pop_front();
```
从容器中删除第一个元素。


### std::forward_list<T,Allocator>::splice_after
将元素从另一个 forward_list 移动到 *this。元素被插入到 pos 指向的元素之后。
```cpp
void splice_after( const_iterator pos, forward_list& other );

void splice_after( const_iterator pos, forward_list&& other );

void splice_after( const_iterator pos, forward_list& other,
                   const_iterator it );

void splice_after( const_iterator pos, forward_list&& other,
                   const_iterator it );

void splice_after( const_iterator pos, forward_list& other,
                   const_iterator first, const_iterator last );

void splice_after( const_iterator pos, forward_list&& other,
                   const_iterator first, const_iterator last );
```