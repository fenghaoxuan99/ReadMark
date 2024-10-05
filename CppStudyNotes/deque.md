<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->
<!-- code_chunk_output -->
- [deque 的内部实现原理：](#deque-的内部实现原理)
- [deque 的内部实现原理：](#deque-的内部实现原理)
- [deque 的插入和删除](#deque-的插入和删除)
- [deque 的数据获取](#deque-的数据获取)

<!-- /code_chunk_output -->


## deque 的内部实现原理：

deque是一个双向队列（double-ended queue），可以在队列的两端进行元素的插入和删除操作。
deque的特点是可以在队列的两端进行元素的操作，并且可以高效地在队列的任意位置进行元素的插入和删除操作。
可以说deque几乎涵盖了queue（队列）、stack（堆栈）、vector（向量 ）等的全部用法，功能非常的强大。

在deque容器的内部有一个中控器的东西，来管理每一小段的数组，数组里面存放真实数据，而中控器存放的是每一小段数组的首地址，当你要插入数据的时候，它会在中控器中寻找，找每一个数组看看是否头部可以插入数据，假如可以就在找到的位置插入，没有的化，就会重新开辟一段内存，指向数组，插入数据。删除头部也是一样。每一段小数组都是连续的，因为中控器的地址也是连续的，使得deque向一个连续的空间。



## deque 的插入和删除
|函数原型            |功能|
|:--:               |--|
|push_back(elem)	|在容器尾部添加一个数据|
|push_front(elem)	|在容器头部插入一个数据|
|pop_back()			|删除容器最后一个数据|
|pop_front()		|删除容器第一个数据|
|insert(pos,elem)	|在pos位置插入一个elem元素的拷贝|
|insert(pos,n,elem)	|在pos位置插入n个elem数据|
|insert(pos,beg,end)|在pos位置插入[beg,end)区间的数据|
|clear()			|清空容器的所有数据|
|erase(beg,end)		|删除[beg,end)区间的数据|
|erase(pos)			|删除pos位置的数据|
|emplace_front()    |与push_front()的作用一样|
|emplace_back()		|与push_back()的作用一样|

## deque 的数据获取
|函数原型|	功能|
|:--:|--|
|at(int idx)|返回索引idx所指的数据|
|operator[]	|返回索引idx所指的数据|
|front()	|获取容器中第一个数据元素|
|back()		|获取容器中最后一个数据元素|






