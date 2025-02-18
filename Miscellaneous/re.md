以下是关于正则表达式的详细说明及在 Python 中的使用方法：

---

### **一、正则表达式基础**

#### 1. 核心概念

- **模式匹配语言**：用于在字符串中查找/替换特定模式的文本
- **组成元素**：普通字符（如 a-z）和元字符（具有特殊含义的符号）

#### 2. 常用元字符

| 元字符 | 说明                           | 示例        |
| ------ | ------------------------------ | ----------- | ---- | ---- |
| `.`    | 匹配任意单个字符（除换行符）   | `a.c` → abc |
| `^`    | 匹配字符串开始位置             | `^Hello`    |
| `$`    | 匹配字符串结束位置             | `world$`    |
| `\d`   | 匹配数字（等同[0-9]）          | `\d{3}`     |
| `\w`   | 匹配字母/数字/下划线           | `\w+`       |
| `\s`   | 匹配空白字符（空格、制表符等） | `\s+`       |
| `[]`   | 字符集合                       | `[aeiou]`   |
| `      | `                              | 或运算      | `cat | dog` |
| `()`   | 定义捕获组                     | `(\d{3})-`  |

#### 3. 量词

| 量词    | 说明        | 示例      |
| ------- | ----------- | --------- |
| `*`     | 0 次或多次  | `a*`      |
| `+`     | 1 次或多次  | `\d+`     |
| `?`     | 0 次或 1 次 | `colou?r` |
| `{n}`   | 恰好 n 次   | `\d{4}`   |
| `{n,}`  | 至少 n 次   | `\w{3,}`  |
| `{m,n}` | m 到 n 次   | `a{2,4}`  |

---

### **二、Python 中的正则模块（re）**

#### 1. 核心方法

| 方法名          | 功能说明                     | 返回值类型      |
| --------------- | ---------------------------- | --------------- |
| `re.match()`    | 从字符串起始位置匹配         | Match 对象/None |
| `re.search()`   | 扫描整个字符串查找第一个匹配 | Match 对象/None |
| `re.findall()`  | 查找所有匹配项               | List            |
| `re.finditer()` | 查找所有匹配项（迭代器）     | 迭代器          |
| `re.sub()`      | 替换匹配内容                 | 新字符串        |
| `re.split()`    | 根据模式分割字符串           | List            |
| `re.compile()`  | 预编译正则表达式             | Pattern 对象    |

#### 2. 匹配标志（Flags）

| 标志         | 说明                 | 简写   |
| ------------ | -------------------- | ------ |
| `IGNORECASE` | 忽略大小写           | `re.I` |
| `MULTILINE`  | 多行模式（影响^和$） | `re.M` |
| `DOTALL`     | 使`.`匹配换行符      | `re.S` |

---

### **三、使用案例**

#### 1. 邮箱验证

```python
import re

pattern = r'^[\w.-]+@([a-zA-Z\d-]+\.)+[a-zA-Z]{2,4}$'
emails = ["test@example.com", "invalid@.com", "name@sub.domain.co.uk"]

for email in emails:
    if re.match(pattern, email):
        print(f"有效邮箱: {email}")
    else:
        print(f"无效邮箱: {email}")
```

#### 2. 电话号码提取

```python
text = "联系客服：400-123-4567 或 021-87654321"
pattern = r'\d{3}-\d{3}-\d{4}|\d{3}-\d{8}'

numbers = re.findall(pattern, text)
print("提取到的电话号码:", numbers)  # ['400-123-4567', '021-87654321']
```

#### 3. HTML 标签内容提取

```python
html = '<div class="content"><h1>标题</h1><p>正文内容</p></div>'

# 提取所有标签内容
tags = re.findall(r'<([a-z]+)(?: .*?)?>(.*?)</\1>', html, re.I|re.S)
print("标签内容:", tags)  # [('div', '<h1>标题</h1><p>正文内容</p>'), ('h1', '标题'), ('p', '正文内容')]
```

#### 4. 日期格式转换

```python
date_str = "2023-09-15"
new_date = re.sub(r'(\d{4})-(\d{2})-(\d{2})', r'\2/\3/\1', date_str)
print(new_date)  # 09/15/2023
```

---

### **四、高级技巧**

#### 1. 分组与捕获

```python
text = "姓名：张三 年龄：25"
pattern = r"姓名：(\w+)\s+年龄：(\d+)"
match = re.search(pattern, text)

if match:
    print(f"姓名: {match.group(1)}, 年龄: {match.group(2)}")
    # 输出：姓名: 张三, 年龄: 25
```

#### 2. 非贪婪匹配

```python
html = '<div>内容1</div><div>内容2</div>'
# 贪婪模式
print(re.findall(r'<div>(.*)</div>', html)[0])  # 内容1</div><div>内容2
# 非贪婪模式
print(re.findall(r'<div>(.*?)</div>', html))    # ['内容1', '内容2']
```

#### 3. 命名分组

```python
text = "IP: 192.168.1.1"
pattern = r"(?P<first>\d{1,3})\.(?P<second>\d{1,3})"
match = re.search(pattern, text)

if match:
    print(match.groupdict())  # {'first': '192', 'second': '168'}
```

---

### **五、性能优化建议**

1. **预编译正则**：

```python
pattern = re.compile(r'\d{4}-\d{2}-\d{2}')
print(pattern.findall("日期：2023-09-15"))
```

2. **避免过度使用`.`**：

```python
# 不推荐
r'<div class=".*?">(.*?)</div>'
# 推荐
r'<div class="[^"]*">(.*?)</div>'
```

3. **合理使用原子组**：

```python
r'(?>\d+)\b'  # 防止回溯
```

---

### **六、调试工具推荐**

1. 在线测试工具：

   - [RegExr](https://regexr.com/)
   - [Regex101](https://regex101.com/)

2. VS Code 插件：
   - **Regex Previewer**
   - **Rainbow CSV**（用于 CSV 正则调试）

通过系统学习这些内容，您将能高效处理各种文本匹配和提取需求。
