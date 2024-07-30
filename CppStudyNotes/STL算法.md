
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [STL算法](#stl算法)
  - [遍历算法](#遍历算法)
    - [for_each 函数](#for_each-函数)
    - [transform 函数](#transform-函数)
  - [查找算法](#查找算法)
    - [find 函数](#find-函数)
    - [find_if 函数](#find_if-函数)
    - [binary_search](#binary_search)
    - [count 函数](#count-函数)
    - [count_if 函数](#count_if-函数)
  - [排序算法](#排序算法)
    - [sort 函数](#sort-函数)
    - [random_shuffle 函数](#random_shuffle-函数)
    - [merge 函数](#merge-函数)
    - [reverse 函数](#reverse-函数)
  - [替换算法](#替换算法)
    - [repalce 函数](#repalce-函数)
    - [replace _if 函数](#replace-_if-函数)

<!-- /code_chunk_output -->



# STL算法
## 遍历算法
- for_each
- transform

### for_each 函数
for_each（iterator begin,iterator end,_func）	
解释参数：
- begin为容器的起始迭代器，
- end为容器的结束迭代器，
- _func为普通函数名字，或者仿函数（函数对象）

### transform 函数
注意：使用transform 时候要为 目标容器开辟空间。用resize函数开辟

transform(iterator beg1, iterator end1, iterator beg2, _func)	搬运一个容器到另一个容器中
解释参数：
- beg1为要被搬运d容器的起始迭代器，
- end1为被搬运容器的结束迭代器，
- beg2为目标容器的起始迭代器，
- _func为普通函数名字，或者仿函数（函数对象）
```cpp
#include<vector>
#include<algorithm>

//常用遍历算法  搬运 transform

class TransForm
{
public:
	int operator()(int val)
	{
		return val;
	}

};

class MyPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	vector<int>vTarget; //目标容器

	vTarget.resize(v.size()); // 目标容器需要提前开辟空间
	
	// TransForm()c参数为TransForm类的匿名对象，也是仿函数（函数对象）
	transform(v.begin(), v.end(), vTarget.begin(), TransForm());

	for_each(vTarget.begin(), vTarget.end(), MyPrint());
}
```

## 查找算法

- find	查找元素
- find_if	按条件查找元素
- adjacent_find	查找相邻重复元素
- binary_search	二分查找法
- count	统计元素个数
- count_if	按条件统计元素个数

### find 函数
函数原型：
find(iterator beg, iterator end, value);
- 功能：
查找容器区间 [beg,end) 中是否又value 值，有返回该值的迭代器位置，并且 break，没有就返回结束迭代器的位置。
- 注意：
在查找自定义数据类型的元素时候，需要自己重载 == 操作符
- 参数解释：
  - beg为容器的起始迭代器
  - end为容器的末尾迭代器
  - value为要查找的元素

### find_if 函数
- 函数原型：
find(iterator beg, iterator end, _Pred);
-功能：
查找容器区间 [beg,end) 中是满足条件 _Pred的值，有返回该值的迭代器位置，并且 break，没有就返回结束迭代器的位置。
- 注意：
在查找自定义数据类型的元素时候，需要自己重载 == 操作符
- 参数解释：
 - beg为容器的起始迭代器；
 - end为容器的末尾迭代器；
 - _Pred为函数名或者谓词（返回bool类型的仿函数）；
总结：
find_if按条件查找使查找更加灵活，提供的仿函数可以改变不同查找的策略。


### binary_search
函数原型：
bool binary_search(iterator beg, iterator end, value)
- 功能：
查找容器区间 [beg,end) 中 value是否存在，存在返回 ture;不存在返回 false；这是比较快速查找的算法
- 注意
查找的容器必须有序，无序会得不到预期的效果
- 参数解释：
 - beg为容器的起始迭代器
 - end为容器的末尾迭代器


### count 函数
函数原型：
count(iterator beg, iterator end, value);
- 功能：
统计容器区间 [beg,end) 中 value出现次数,返回 value出现的次数；
- 注意：
统计自定义数据类型需要重载==，返回类型为bool
- 参数解释：
 - beg为容器的起始迭代器；
 - end为容器的末尾迭代器；
 - value为要统计的元素；

### count_if 函数
函数原型：
count_if(iterator beg, iterator end, _Pred);
- 功能：
统计容器区间 [beg,end) 中 value出现次数；
- 参数解释：
 - beg为容器的起始迭代器；
 - end为容器的末尾迭代器；
 - _Pred为函数名或谓词；

#### 对于自定义的数据类型，需要在类中重载== 操作符
```cpp
#include <algorithm>
#include <vector>
#include <string>
void test01() {

	vector<int> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(i + 1);
	}
	//查找容器中是否有 5 这个元素
	vector<int>::iterator it = find(v.begin(), v.end(), 5);
	if (it == v.end()) 
	{
		cout << "没有找到!" << endl;
	}
	else 
	{
		cout << "找到:" << *it << endl;
	}
}

class Person {
public:
	Person(string name, int age) 
	{
		this->m_Name = name;
		this->m_Age = age;
	}
	//重载==
	bool operator==(const Person& p) 
	{
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age) 
		{
			return true;
		}
		return false;
	}

public:
	string m_Name;
	int m_Age;
};

void test02() {

	vector<Person> v;

	//创建数据
	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
 //查找自定义的数据类型				
	vector<Person>::iterator it = find(v.begin(), v.end(), p2);
	if (it == v.end()) 
	{
		cout << "没有找到!" << endl;
	}
	else 
	{
		cout << "找到姓名:" << it->m_Name << " 年龄: " << it->m_Age << endl;
	}
}
```

## 排序算法
- sort	对容器内元素进行排序
- random_shuffle	随机洗牌 指定范围内的元素随机调整次序 指定范围内的元素随机调整次序
- merge	容器元素合并，并存储到另一容器中
- reverse	反转指定范围的元素

### sort 函数
- 函数原型：
sort(iterator beg, iterator end, _Pred);
- 功能：
默认按升序排序容器区间 [beg,end) ，_Pred为排序策略通常为了降序时候才写的谓词
- 参数解释：
beg为容器的起始迭代器
end为容器的末尾迭代器
_Pred为函数名或谓词


### random_shuffle 函数
函数原型：
random_shuffle(iterator beg, iterator end);
- 功能：
随机打乱容器里[beg,end)的元素位置；
注意：一般这个函数使用要搭载随机数种子 srand( (unsigned int) time(NULL));
- 参数解释：
beg为容器的起始迭代器
end为容器的末尾迭代器

### merge 函数
- 函数原型：
merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest)
- 功能：
将两个容器合并并且按升序的方式到目标容器中
- 注意：
两个容器必须有序，目标容器需要开辟空间
- 参数解释：
 - beg1为容器1的起始迭代器
 - end1为容器1的末尾迭代器
 - beg2为容器2的起始迭代器
 - end2为容器2的末尾迭代器
 - dest为目容器的起始迭代器
```cpp
#include <algorithm>
#include <vector>

class myPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test01()
{
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < 10 ; i++) 
    {
		v1.push_back(i);
		v2.push_back(i + 1);
	}

	vector<int> vtarget;
	//目标容器需要提前开辟空间
	vtarget.resize(v1.size() + v2.size());
	//合并  需要两个有序序列
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vtarget.begin());
	for_each(vtarget.begin(), vtarget.end(), myPrint());
	cout << endl;
}
```

### reverse 函数
- 函数原型：
reverse(iterator beg, iterator end);
- 功能：
反转容器[beg,end）范围的数据
- 参数解释：
 - beg为容器的起始迭代器
 - end为容器的末尾迭代器

## 替换算法
- replace	将容器内指定范围的旧元素修改为新元素
- replace_if	容器内指定范围满足条件的元素替换为新元素
- swap	互换两个容器的元素

### repalce 函数
函数原型：
replace(iterator beg, iterator end, oldvalue, newvalue);
- 功能：
将容器中从[beg，end)位置的元素，由 oldvalue,替换成newvalue;
- 参数解释：
beg为容器的起始迭代器
end为容器的末尾迭代器
oldvalue为容器的要被替换的元素
newvalue为新的元素

### replace _if 函数
函数原型：
replace(iterator beg, iterator end, pred, newvalue);

功能：
将容器中从[beg，end)位置的元素，以，_Pred作为条件将_Perd条件的元素替换成newvalue;

参数解释：
beg为容器的起始迭代器；
end为容器的末尾迭代器；
pred为函数名或者仿函数
newvalue为新的元素；