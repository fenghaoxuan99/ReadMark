



map()函数是Python中的一个内置函数，它的功能是：将指定的函数，依次作用于可迭代对象的每个元素，并返回一个迭代器对象。这个可迭代对象，可以是一个也可以是多个。
二、map（）函数的语法
语法

map(function,iterable,...)
参数

function-我们指定的函数（或数据类型），可以是python内置的，也可以是自定义的。

iterable-可迭代的对象，例如列表，元组，字符串等。

返回值

返回一个可迭代对象，一般搭配list()使用，输出列表

```py
#自定义一个函数a,返回x*2的值
def a(x):
    return x*2
 
#定义列表
lis1=[1,3,5,7,9]
 
#对列表中的每个数运用函数a，返回迭代器
lis1_a=map(a,lis1)
 
#输出迭代器中的值
for num in lis1_a:
    print(num)
    
#输出结果
'''
2
6
10
14
18
'''
```

```py
#定义一个列表a
a = ['1','2','3']
 
#将列表中的每个字符串，转换成浮点型，并返回迭代器
b = map(float,a)
 
#输出迭代器中的值
for num in b:
    print(num)
 
#输出结果
'''
1.0
2.0
3.0
'''
```

四、运行结果出现：<map object at 0x000001809CD03400>
map函数直接返回一个可迭代对象，直接打印输出会输出地址

```py
a = ['1','3','5']
b = map(int,a)
print(b)
print(type(b))
 
#输出结果
'''
<map object at 0x0000025781BBB610>
<class 'map'>
'''
```