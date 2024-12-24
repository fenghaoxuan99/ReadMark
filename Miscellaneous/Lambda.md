<!--
 * @Author: feng 1804831168@qq.com
 * @Date: 2024-07-08 15:03:04
 * @LastEditors: feng 1804831168@qq.com
 * @LastEditTime: 2024-12-24 21:01:14
 * @Description: 
 * Copyright (c) 2024 by Feng, All Rights Reserved. 
-->
# Lambda 表达式

lambda [参数列表]:表达式

### 英文语法格式：

lambda [arg1[,arg2,arg3....argN]]:expression

## 格式中有一些注意事项：

lambda 表达式必须使用 `lambda` 关键字定义；
lambda 关键字后面，冒号前面是参数列表，参数数量可以从 0 到任意个数。多个参数用逗号分隔，冒号右边是 lambda 表达式的返回值。

1. **基本结论就是：lambda 表达式只允许包含一个表达式，不能包含复杂语句，该表达式的运算结果就是函数的返回值。**
2. lambda 表达式一般用于无需多次使用的函数，并且该函数使用完毕就释放了所占用的空间
3. **for 语句不能用在 lambda 中**

## lambda 表达式可以作为其它数据类型的值

例如下述代码，用 lambda 表达式是没有问题的。

```py
# 使用Lambda函数和map()函数将列表中的每个元素都平方
numbers = [1, 2, 3, 4, 5]
squared = list(map(lambda x: x * x, numbers))
print(squared)  # 输出: [1, 4, 9, 16, 25]

# 使用Lambda函数和filter()函数筛选出列表中的偶数
even_numbers = list(filter(lambda x: x % 2 == 0, numbers))
print(even_numbers)  # 输出: [2, 4]
```

## lambda 表达式可以作为其它函数的参数

```py
# 使用Lambda函数定义一个自定义的排序规则
students = [
    {'name': 'Tiyong', 'grade': 90},
    {'name': 'Bob', 'grade': 85},
    {'name': 'Toy', 'grade': 95}
]

# 按照学生的成绩进行排序
sorted_students = sorted(students, key=lambda x: x['grade'], reverse=True)
print(sorted_students)

# 输出：[{'name': 'Toy', 'grade': 95}, {'name': 'Tiyong', 'grade': 90}, {'name': 'Bob', 'grade': 85}]
```
