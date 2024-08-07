

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [deque 的内部实现原理：](#deque-的内部实现原理)
- [deque 的插入和删除](#deque-的插入和删除)
- [deque 的数据获取](#deque-的数据获取)
- [命名空间](#命名空间)

<!-- /code_chunk_output -->


## deque 的内部实现原理：
在deque容器的内部有一个中控器的东西，来管理每一小段的数组，数组里面存放真实数据，而中控器存放的是每一小段数组的首地址，当你要插入数据的时候，它会在中控器中寻找，找每一个数组看看是否头部可以插入数据，假如可以就在找到的位置插入，没有的化，就会重新开辟一段内存，指向数组，插入数据。删除头部也是一样。每一段小数组都是连续的，因为中控器的地址也是连续的，使得deque向一个连续的空间。
不那么快的原因是因为：需要从中控器中找到地址，在去访问数组的元素。导致有点慢。


## deque 的插入和删除
|函数原型	|功能|
|:--:|--|
|push_back(elem)	|在容器尾部添加一个数据|
|push_front(elem)	|在容器头部插入一个数据|
|pop_back()	|删除容器最后一个数据|
|pop_front()	|删除容器第一个数据|
|insert(pos,elem)	|在pos位置插入一个elem元素的拷贝|
|insert(pos,n,elem)	|在pos位置插入n个elem数据|
|insert(pos,beg,end)	|在pos位置插入[beg,end)区间的数据|
|clear()	|清空容器的所有数据|
|erase(beg,end)	|删除[beg,end)区间的数据|
|erase(pos)|	删除pos位置的数据|

## deque 的数据获取
|函数原型|	功能|
|:--:|--|
|at(int idx)	|返回索引idx所指的数据|
|operator[]	|返回索引idx所指的数据|
|front()|	获取容器中第一个数据元素|
|back()|	获取容器中最后一个数据元素|



## 命名空间
命名空间就是为了防止名字冲突而引入的一种机制。
自定义的命名空间名字，不可以相同，但是可以定义多个命名空间；
一个命名空间里面的成员函数名，类型名，变量名，都可以与其他命名空间名字里面的相同；因为不同的命名空间，相当于不同的作用域；

```cpp
1. 命名空间的定义：
namespace 命名空间名
{
	这里可以定义任何的东西
	如：void a();
}
2. 命名空间可以不连续定义：即，你可以在任意位置定义命名空间，但假如你定义命名空间时候，已经有了同名命名空间名，
这就相当于给已经有的命名空间重新添加新的内容进去

3. 外界访问命名空间里面的内容：
命名空间名:: 内容（函数调用，变量名，类型名等）；
还可以通过：using namespace 命名空间名；
声明后，你该命名空间里面的内容就不需要使用：命名空间名::内容；方式访问了，
直接使用 内容的方式就可以；
直接 using声明 命名空间，也有不好的地方，一旦你的不同命名空间都使用using声明的话，
这不同命名空间中又同名的内容，在访问的同名内容时候，就会发生编译错误，这就导致二义性。
```





