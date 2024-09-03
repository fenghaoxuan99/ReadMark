


## stack 的常用接口
stack<T> s: 			初始化空栈；
stack(const stack &s)：	拷贝栈；
stack& operator=(const stack &s):赋值栈
push(elem): 			向栈顶添加元素
pop():					从栈顶移除第一个元素
top():					 返回栈顶元素
empty(): 				判断堆栈是否为空
size(): 				返回栈的大小

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
