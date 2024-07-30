

## STL的六大组件
1. 容器：各种模板的数据结构，如vector,string,deque,set,map等，就是用来存储数据用的。
2. 算法：各种常用算法，如sort、find、copy、for_each等。
3. 迭代器：容器和算法之间的联系桥廊，可以理解为指针；
4. 配接器：一种用来修饰容器或者仿函数或迭代器接口的东西。
5. 仿函数：行为类似函数，可作为算法的某种策略。
6. 空间适配器：负责空间的配置与管理。


## vector 的构造函数
功能：创建vector容器；

|调用时构造函数原型	|功能描述|
|:--:|--|
|vector< T > v	                 |类模板的方式，默认构造|
|vector< T > v1(v.begin, v.end)	 |将v[begin(), end())区间中的元素拷贝给v1,注意是左闭右开区间|
|vector< T > v(n,elem)           |构造函数将n个elem拷贝给v|
|vector< T > v(const vector &vec)|将 vec 容器拷贝到 v|

```cpp
#include <vector>
void printVector(vector<int>& v) {

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	//无参构造
	vector<int> v1; 
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	printVector(v1); 
	
	//将v1[begin(), end())区间中的元素拷贝给v2
	vector<int> v2(v1.begin(), v1.end());
	printVector(v2);
	
	//构造函数将10个100拷贝给v3
	vector<int> v3(10, 100);
	printVector(v3);
	
	//将v3拷贝到v4中；
	vector<int> v4(v3);
	printVector(v4);
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

## vector 容量和大小操作
|调用时的函数原型	|功能|
|:--:|--|
|v.empty()	    |判断v容器是否为空，空返回假，不空返回真|
|v.capacity()	|计算v容器的容量大小|
|v.size()	    |计算v容器的元素个数|
|v.resize(num)	|重新指定容器的长度为num，若容器变长，则以默认值 0 填充新位置如果容器变短，则末尾超出容器长度的元素被删除。|
|v.resize(num,elem)	|重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除|

## vector 的插入和删除

|接口函数原型	|功能|
|:--:|--|
|push_back(ele)	                                |插入元素ele|
|pop_back()                        			    |删除最后一个元素|
|insert(const_iterator pos, ele)                |向迭代器指向位置pos插入元素ele|
|insert(const_iterator pos, int count,ele)	    |迭代器指向位置pos位置，插入count个ele元素|
|erase(const_iterator pos)	                    |删除迭代器指向位置pos的元素|
|erase(const_iterator start, const_iterator end)|删除迭代器从start到end之间的元素，注意区间是左闭右开|
|clear()	                                    |删除容器中所有元素|

## vector 的数据存取操作
我们可以通过迭代器去访问vector容器的数据，也可以通过vector容器提供的成员函数去访问；

|调用时候的成员函数原型	|功能|
|:--:|--|
|v [ i ]	|访问v容器的下标为i的元素|
|v.at( i )	|访问v容器的下标为i的元素|
|v.front( ) |取v容器的第一个元素|
|v.back( )	|取v容器的最后一个元素|

## vector 的swap函数收缩空间
|被调函数原型|功能|
|:--:|--|
|v.shrink_to_fit()	|将vector容器的容量收缩到和大小一样|
|v.swap(vec)        |将vec容器于v容器交换数据|

```cpp
void test02()
{
	vector<int> v;
	//向容器插入大量数据，10万个数据
	for (int i = 0; i < 100000; i++) {
		v.push_back(i);
	}

	cout << "v的容量为：" << v.capacity() << endl;
	cout << "v的大小为：" << v.size() << endl;

	v.resize(3);// 重新指定容器大小，由于前面插入十万个数据，
	//开辟的容器容量很大，这里重新指定为3个大小，
	//导致容量不变，数据只有3个，这会大量浪费空间。

	cout << "v的容量为：" << v.capacity() << endl;
	cout << "v的大小为：" << v.size() << endl;

	//收缩内存
	vector<int>(v).swap(v); //vector<int>(v)匿名对象

	cout << "v的容量为：" << v.capacity() << endl;
	cout << "v的大小为：" << v.size() << endl;
}

```
具体来说，swap 函数交换两个 vector 对象的内部数据，包括它们存储的元素、分配的内存、以及它们的大小和容量。交换后，原始的 v 将拥有副本的内存，而副本则拥有原始 v 的内存。由于副本是新创建的，它的容量是0，这意味着它实际上没有分配任何内存。

交换后，原始 v 的内存被清空，因为其内容被转移到了副本中，而副本则被销毁，释放了它所占用的内存。这样，原始 v 的内存使用量就减少了，实现了所谓的“内存收缩”。

但是，需要注意的是，这种写法在某些情况下可能不会达到预期效果，特别是当 vector 被用作其他容器的元素或者作为对象成员时。这是因为 swap 函数可能会违反对象的所有权规则。正确的内存收缩方法应该是直接调用 vector 的 shrink_to_fit 方法，如果编译器支持 C++11 或更高版本的话

## reserve(int size) 预留size个空间。
功能：在提前知道数据大小的情况下，使用reserve函数能够预留出你需要的空间，减少了动态扩容时候开辟空间的次数