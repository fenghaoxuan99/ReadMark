


## 使用大括号 {} 创建空字典：
my_dict = {}
 
 
## 使用键值对创建字典：
my_dict = {'key1': 'value1', 'key2': 'value2', 'key3': 'value3'}
 
 
## 使用 dict() 构造函数：
my_dict = dict(key1='value1', key2='value2', key3='value3')
 
## 使用列表/元组的列表转换为字典：
```py
列表中每个元素是一个包含键值对的元组
my_list = [('key1', 'value1'), ('key2', 'value2'), ('key3', 'value3')]
my_dict = dict(my_list)
```

## 或者使用zip函数
```py
keys   = ['key1', 'key2', 'key3']
values = ['value1', 'value2', 'value3']
my_dict = dict(zip(keys, values))
```
 
## 使用推导式出创建一个列表
```py
# 创建一个简单的字典，键为数字 0 到 4，值为它们的平方
my_dict = {x: x**2 for x in range(5)}
print(my_dict)
# 输出: {0: 0, 1: 1, 2: 4, 3: 9, 4: 16}
```


my_dict = {"a": 1, "b": 2}
# 使用 update() 方法批量添加或更新键值对
```py
my_dict.update({"d": 4, "e": 5})
 
print(my_dict)
# 输出: {'a': 1, 'b': 5, 'c': 3, 'd': 4, 'e': 5}
```

my_dict = {"a": 1, "b": 2}
# 使用 setdefault() 方法添加键值对，但仅在键不存在时
my_dict.setdefault("f", 6)
 
print(my_dict)
# 输出: {'a': 1, 'b': 2, 'f': 6}
 
# 如果键已存在，则不会进行任何操作
my_dict.setdefault("a", 10)
 
print(my_dict)
# 输出:{'a': 1, 'b': 2, 'f': 6}


my_dict = {"a": 1, "b": 2, "c": 3}
 
# 删除键为 "b" 的键值对，并返回被删除的值
deleted_value = my_dict.pop("b")
 
print(deleted_value)  # 输出: 2
print(my_dict)        # 输出: {'a': 1, 'c': 3}