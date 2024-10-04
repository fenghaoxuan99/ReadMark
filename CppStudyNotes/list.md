
# list 容器
- 概念：
list 容器就是一个==双向循环链表==
- 说明：
list 容器是本质是链表，地址存储不是连续空间的，所以不支持随机访问，所以迭代器不可以跳跃式访问其他空间的位置，就是你不可以任意的访问其他空间的元素;
list 的迭代器支++ 和 – 的操作,不支持 +1 的操作。
- 优点：
 - 相对于vector 容器来说，list 插入数据不会造成浪费空间；在 vector 插入数据时候，会开辟一段空间，通常比原有的数据大1.5倍左右，而list容器，你用到多少数据，就开辟多少空间。
 - 相对于 vector 容器来说，list 插入和删除元素的速度比较快，因为只需要找到数据的位置，修改指针域就行，不像vector 插入删除时候要大量移动数据；


|函数原型|	功能|
|:--:|:--|
|push_back(elem)	|尾插elem|
|pop_back()	        |尾删|
|push_front(elem)	|头插elem|
|pop_front()	    |头删|
|insert(pos,elem)	|在迭代器 pos 位置 插入elem|
|insert(pos,n,elem)	|在迭代器pos 位置插入 n个elem|
|insert(pos,beg,end)|在 迭代器 pos 的位置插入区间[beg,end)的元素|
|clear()	        |移除容器的所有数据|
|erase(beg,end)	    |删除[beg,end)区间的数据|
|erase(pos)    	    |删除迭代器pos位置的元素|
|remove(elem)	    |删除容器中所有与elem值匹配的元素。|

begin()		// 返回指向容器中第一个元素的双向迭代器。
end()		// 返回指向容器中最后一个元素所在位置的下一个位置的双向迭代器。
rbegin()	// 返回指向最后一个元素的反向双向迭代器。
rend()		// 返回指向第一个元素所在位置前一个位置的反向双向迭代器。
cbegin()	// 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
cend()		// 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
crbegin()	// 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
crend()		// 	和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。




#### std::list<T,Allocator>::reverse
1. void reverse();
2. void reverse() noexcept;
```cpp
#include <iostream>
#include <list>
 
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}
 
int main()
{
    std::list<int> list = { 8,7,5,9,0,1,3,2,6,4 };
 
    std::cout << "before:     " << list << "\n";
    list.sort();
    std::cout << "ascending:  " << list << "\n";
    list.reverse();
    std::cout << "descending: " << list << "\n";
}
```


#### std::list<T,Allocator>::unique
从容器移除所有相继的重复元素。只留下相等元素组中的第一个元素。

#### std::list<T,Allocator>::sort
```cpp
int main()
{
    std::list<int> list = { 8,7,5,9,0,1,3,2,6,4 };
 
    std::cout << "before:     " << list << "\n";
    list.sort();
    std::cout << "ascending:  " << list << "\n";
    list.sort(std::greater<int>());
    std::cout << "descending: " << list << "\n";
}
```
#### std::list<T,Allocator>::assign
1. void assign( size_type count, const T& value );
2. template< class InputIt >
void assign( InputIt first, InputIt last );
3. void assign( std::initializer_list<T> ilist );

```cpp
int main()
{
    std::list<char> characters;
 
    characters.assign(5, 'a');
 
    for (char c : characters) {
        std::cout << c << ' ';
    } 
 
    characters.assign({'\n', 'C', '+', '+', '1', '1', '\n'});
 
    for (char c : characters) {
        std::cout << c;
    }

```

#### std::list<T,Allocator>::merge
归并二个已排序链表为一个。链表应以升序排序。
1. void merge( list& other );
2. void merge( list&& other );
3. template <class Compare>
void merge( list& other, Compare comp );
4. template <class Compare>
void merge( list&& other, Compare comp );


other	-	要交换的另一容器
comp	-	比较函数对象（即满足比较 (Compare) 概念的对象），若第一参数小于（即先序于）第二参数则返回 ​true 。
比较函数的签名应等价于如下：

 bool cmp(const Type1 &a, const Type2 &b);


#### std::list<T,Allocator>::remove, remove_if
1. void remove( const T& value );
2. size_type remove( const T& value );
3. template< class UnaryPredicate >
void remove_if( UnaryPredicate p );
4. template< class UnaryPredicate >
size_type remove_if( UnaryPredicate p );
移除所有满足特定标准的元素。第一版本移除所有等于 value 的元素，第二版本移除所有谓词 p 对它返回 true 的元素。
参数
value	-	要移除的元素的值
p	   -	若应该移除该元素则返回 ​true 的一元谓词。

```cpp
int main()
{
    std::list<int> l = { 1,100,2,3,10,1,11,-1,12 };
 
    l.remove(1); // 移除两个等于 1 的元素
    l.remove_if([](int n){ return n > 10; }); // 移除全部大于 10 的元素
 
    for (int n : l) {
        std::cout << n << ' '; 
    }
    std::cout 
```


## 	std::forward_list	
std::forward_list 是支持从容器中的任何位置快速插入和移除元素的容器。不支持快速随机访问。
它实现为单链表，且实质上与其在 C 中实现相比无任何开销。与 std::list 相比，此容器在不需要双向迭代时提供更有效地利用空间的存储。

#### std::forward_list<T,Allocator>::emplace_after
在容器中的指定位置后插入新元素。原位构造元素，即不进行复制或移动操作。

1. template< class... Args >
iterator emplace_after( const_iterator pos, Args&&... args );

##### 参数
pos  - 新元素将构造于其后的迭代器
args - 转发给元素构造函数的参数
##### 返回值
指向新元素的迭代器。

```cpp
int main()
{
    std::forward_list<Sum> list;
 
    auto iter = list.before_begin();
    std::string str{"1"};
    for (int i{1}, sum{1}; i != 10; sum += i) {
        iter = list.emplace_after(iter, str, sum);
        ++i;
        str += " + " + std::to_string(i);
    }
 
    for (const Sum& s : list) s.print();
}
```

#### std::forward_list<T,Allocator>::insert_after
1. iterator insert_after( const_iterator pos, const T& value );
2. iterator insert_after( const_iterator pos, T&& value );
3. iterator insert_after( const_iterator pos, size_type count, const T& value );
4. template< class InputIt >
iterator insert_after( const_iterator pos, InputIt first, InputIt last );
5. iterator insert_after( const_iterator pos, std::initializer_list<T> ilist );

```cpp
#include <forward_list>                                                         
#include <string>                                                               
#include <iostream>                                                             
#include <vector>                                                               
 
template<typename T>                                                            
std::ostream& operator<<(std::ostream& s, const std::forward_list<T>& v) {      
    s.put('[');                                                                 
    char comma[3] = {'\0', ' ', '\0'};                                          
    for (const auto& e : v) {                                                   
        s << comma << e;                                                        
        comma[0] = ',';                                                         
    }                                                                           
    return s << ']';                                                            
}                                                                               
 
int main()                                                                      
{                                                                               
    std::forward_list<std::string> words {"the", "frogurt", "is", "also", "cursed"};
    std::cout << "words: " << words << '\n';                                    
 
    // insert_after (2)                                                         
    auto beginIt = words.begin();                                               
    words.insert_after(beginIt, "strawberry");                                  
    std::cout << "words: " << words << '\n';                                    
 
    // insert_after (3)                                                         
    auto anotherIt = beginIt;                                                   
    ++anotherIt;                                                                
    anotherIt = words.insert_after(anotherIt, 2, "strawberry");                 
    std::cout << "words: " << words << '\n';                                    
 
    // insert_after (4)
    std::vector<std::string> V = { "apple", "banana", "cherry"};                
    anotherIt = words.insert_after(anotherIt, V.begin(), V.end());              
    std::cout << "words: " << words << '\n';                                    
 
    // insert_after (5)                                                         
    words.insert_after(anotherIt, {"jackfruit", "kiwifruit", "lime", "mango"});
    std::cout << "words: " << words << '\n';                                    
}
```