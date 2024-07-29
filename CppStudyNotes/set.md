



# set 和 multiset容器的基本概念
概念：
set 容器 为集合；multiset 也是集合；插入数据时候默认按升序排列。

说明：
set 和 multiset 的操作基本一致，区别在于，set容器不可以有重复的数据，而multiset可以又重复的数据；
即使你插入的数据是无序序列，set容器也会自动帮你排好顺序；
set 容器插入时候没有push_back()的操作，只有insert（）的操作；


|函数原型|功能|
|:--:|--|
|insert(elem)	 |在容器中插入elem元素|
|clear()	     |清除所有元素|
|erase(pos)      |删除pos迭代器所指的元素|
|erase(beg, end) |删除区间[beg,end)的所有元素|
|erase(elem)	 |删除容器中值为elem的元素|