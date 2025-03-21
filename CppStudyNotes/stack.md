


```cpp
template<
    class T,
    class Container = std::deque<T>
> class stack;
```
std::stack 类是一个容器适配器，它为程序员提供了堆栈的功能 - 具体来说，是一种 LIFO（后进先出）数据结构。

- T	-	存储元素的类型。如果 T 与 Container::value_type 不是同一类型，则程序是非良构的。
- Container	-	用于存储元素的底层容器的类型。容器必须满足SequenceContainer的要求。此外，它必须提供具有常用语义的以下函数
  - back()，例如，std::vector::back()，
  - push_back()，例如，std::deque::push_back()，
  - pop_back()，例如，std::list::pop_back()。
标准容器 std::vector（包括 std::vector<bool>）、std::deque 和 std::list 满足这些要求。默认情况下，如果未为特定的堆栈类实例化指定容器类，则使用标准容器 std::deque。




## stack 的常用接口
|||
|:--:|:--:|
|stack<T> s: 			|初始化空栈；|
|stack(const stack &s)：|	拷贝栈；|
|stack& operator=(const stack &s):|赋值栈|
|push(elem): 			|向栈顶添加元素|
|pop():					|从栈顶移除第一个元素|
|top():					|返回栈顶元素|
|empty(): 				|判断堆栈是否为空|
|size(): 				|返回栈的大小|


#### std::stack<T,Container>::emplace()
```cpp
template< class... Args >
void emplace( Args&&... args );
```
将新元素推到堆栈顶部。元素被就地构造，即不执行复制或移动操作。元素的构造函数使用与提供给函数的参数完全相同的参数调用。


```cpp
#include <stack>
//栈容器常用接口
void test01()
{
	//创建栈容器 栈容器必须符合先进后出
	stack<int> s;

	//向栈中添加元素，叫做 压栈 入栈
	s.push(10);
	s.push(20);
	s.push(30);

	while (!s.empty()) {
		//输出栈顶元素：30 20 10
		cout << "栈顶元素为： " << s.top() << endl;
		//弹出栈顶元素
		s.pop();
	}
	//输出结果：0
	cout << "栈的大小为：" << s.size() << endl;

}
```
