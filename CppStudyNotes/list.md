

# list 容器的基本概念
- 概念：
list 容器就是一个双向循环链表；
- 说明：

list 容器是本质是链表，地址存储不是连续空间的，所以不支持随机访问，所以迭代器不可以跳跃式访问其他空间的位置，就是你不可以任意的访问其他空间的元素;
list 的迭代器支++ 和 – 的操作,不支持 +1 的操作。
- 优点：
 - 相对于vector 容器来说，list 插入数据不会造成浪费空间；在 vector 插入数据时候，会开辟一段空间，通常比原有的数据大1.5倍左右，而list容器，你用到多少数据，就开辟多少空间。
 - 相对于 vector 容器来说，list 插入和删除元素的速度比较快，因为只需要找到数据的位置，修改指针域就行，不像vector 插入删除时候要大量移动数据；


|函数原型|	功能|
|:--:|--|
|push_back(elem)	|尾插elem|
|pop_back()	        |尾删|
|push_front(elem)	|头插elem|
|pop_front()	    |尾删|
|insert(pos,elem)	|在迭代器 pos 位置 插入elem|
|insert(pos,n,elem)	|在迭代器pos 位置插入 n个elem|
|insert(pos,beg,end)|在 迭代器 pos 的位置插入区间[beg,end)的元素|
|clear()	        |移除容器的所有数据|
|erase(beg,end)	    |删除[beg,end)区间的数据|
|erase(pos)    	    |删除迭代器pos位置的元素|
|remove(elem)	    |删除容器中所有与elem值匹配的元素。|