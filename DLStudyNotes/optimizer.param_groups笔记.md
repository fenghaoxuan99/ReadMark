

## optimizer.param_groups用法的示例分析
optimizer.param_groups： 是一个list，其中的元素为字典；

optimizer.param_groups[0]：长度为7的字典，包括[‘params’, ‘lr’, ‘betas’, ‘eps’, ‘weight_decay’, ‘amsgrad’, ‘maximize’]这7个参数；

下面用的Adam优化器创建了一个optimizer变量：
```cpp
optimizer.param_groups[0].keys()
dict_keys(['params', 'lr', 'betas', 'eps', 'weight_decay', 'amsgrad', 'maximize'])
```
平时写代码如何动态修改学习率（常规操作）:
```cpp
for param_group in optimizer.param_groups:
    param_group["lr"] = lr 

```