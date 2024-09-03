

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->
<!-- code_chunk_output -->
- [queue 容器的基本概念](#queue-容器的基本概念)
- [queue 容器的基本概念](#queue-容器的基本概念)


<!-- /code_chunk_output -->

## queue 容器的基本概念
- 概念：queue是一种先进先出(First In First Out,FIFO)的数据结构，队列容器允许从一端插入元素，从另一端移除元素。
- 说明：
通常队头为移除数据，队尾插入数据；
队列没有迭代器的操作，因为无法遍历数据，只能在队头和队尾操作数据；
![d](..\Image\\queue.jpeg)

## queue 容器的基本操作
|函数原型|功能|
|:--:|--|
|size()	            |返回容器中元素的个数|
|empty()	        |判断容器是否为空|
|resize(num)	    |重新指定容器的长度为num，若容器变长，填充 0；如果容器变短，则末尾超出容器长度的元素被删除|
|resize(num, elem)	|重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。|
|push(elem)         |向队尾插入元素|
|pop()	            |移除队头元素|
|back()	            |获取队尾元素|
|front()	        |获取队头元素|







