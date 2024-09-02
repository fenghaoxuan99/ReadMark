

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [queue 容器的基本概念](#queue-容器的基本概念)
- [queue 容器的基本操作](#queue-容器的基本操作)
- [queue容器的插入和删除操作](#queue容器的插入和删除操作)

<!-- /code_chunk_output -->



## queue 容器的基本概念
- 概念：queue是一种先进先出(First In First Out,FIFO)的数据结构，队列容器允许从一端插入元素，从另一端移除元素。
- 说明：
通常队头为移除数据，队尾插入数据；
队列没有迭代器的操作，因为无法遍历数据，只能在队头和队尾操作数据；


## queue 容器的基本操作
|函数原型|功能|
|:--:|--|
|size()	        |返回容器中元素的个数|
|empty()	    |判断容器是否为空|
|resize(num)	|重新指定容器的长度为num，若容器变长，填充 0；如果容器变短，则末尾超出容器长度的元素被删除|
|resize(num, elem)	|重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。|
|push(elem)|向队尾插入元素|
|pop()	        |移除队头元素|
|back()	        |获取队尾元素|
|front()	    |获取队头元素|

## queue容器的插入和删除操作
|函数原型|	功能|
|:--:|--|
|push_back(elem)	|尾插elem|
|pop_back()      	|尾删|
|push_front(elem)	|头插elem|
|pop_front()	    |尾删|
|insert(pos,elem)	|在迭代器 pos 位置 插入elem|
|insert(pos,n,elem)	|在迭代器pos 位置插入 n个elem|
|insert(pos,beg,end)|在 迭代器 pos 的位置插入区间[beg,end)的元素|
|clear()	        |移除容器的所有数据|
|erase(beg,end)  	|删除[beg,end)区间的数据|
|erase(pos)	        |删除迭代器pos位置的元素|
|remove(elem)	    |删除容器中所有与elem值匹配的元素。|


