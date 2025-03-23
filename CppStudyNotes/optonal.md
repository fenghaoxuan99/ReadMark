

`std::optional` 是 C++17 引入的模板类，用于表示一个可能包含值（类型为 `T`）或“无值”的状态。它提供了一种类型安全且显式的方式处理可能缺失的值，避免了使用特殊标记值（如 `nullptr`、`-1` 等）或额外的 `bool` 变量来标识有效性。

---

### **核心功能**
- 明确表达值的“存在”或“不存在”，避免歧义。
- 直接存储值（不依赖动态内存分配），性能高效。
- 替代传统方案（如指针、`std::pair<T, bool>` 或特殊值），提升代码可读性。

---

### **基本用法**

##### std::nullopt 
```cpp
inline constexpr nullopt_t nullopt{/*unspecified*/};
```
**std::nullopt 是 std::nullopt_t 类型的常量。用于指示 std::optional 不包含值。**


#### 1. **创建与初始化**
```cpp
template< class T >
constexpr std::optional<std::decay_t<T>> make_optional( T&& value );

template< class T, class... Args >
constexpr std::optional<T> make_optional( Args&&... args );

template< class T, class U, class... Args >
constexpr std::optional<T> make_optional( std::initializer_list<U> il,  Args&&... args );
```


```cpp
#include <optional>
#include <string>

std::optional<int> opt1;                   // 默认构造，无值
std::optional<std::string> opt2 = "Hello"; // 隐式构造
std::optional<double> opt3 = std::nullopt; // 显式无值

// 使用 std::in_place 构造（避免临时对象）
std::optional<std::vector<int>> opt4(std::in_place, {1, 2, 3});

// 使用工厂函数构造
auto opt5 = std::make_optional(3.14);
```

##### std::optional<T>::emplace  原位构造
```cpp
template< class... Args >
T& emplace( Args&&... args );
```
**就地构造所含值** 如果 *this 在调用前已包含值，则会调用其析构函数销毁所含值。


##### std::optional<T>::swap 与 other 的内容交换。
```cpp
void swap( optional& other ) noexcept(
```
与 other 的内容交换。

如果 *this 和 other 都不含值，则此函数无效果。

#### 2. **赋值与重置**
```cpp
std::optional<int> opt;
opt = 42;       // 赋值
opt = std::nullopt; // 重置为无值
opt.reset();    // 同上
```

#### 3. **检查值是否存在**
- **std::optional<T>::reset**如果 *this 包含一个值，则销毁该值，如同调用 value().T::~T()。 否则，没有效果。
```cpp
if (opt.has_value()) { /* 值存在 */ }
// 或直接转换为 bool
if (opt) { /* 值存在 */ }
```

#### 4. **访问值**

- **std::optional<T>::value** 对包含值的引用。
- **std::optional<T>::value_or** 如果 *this 包含值，则返回包含的值，否则返回 default_value。

```cpp
// 安全访问（若不存在则抛出 std::bad_optional_access）
int value1 = opt.value();

// 提供默认值
int value2 = opt.value_or(0);

// 直接访问（需确保值存在，否则未定义行为）
int value3 = *opt;
auto size = opt->size(); // 假设 T 是 std::vector



#include <cstdlib>
#include <iostream>
#include <optional>

std::optional<const char *> maybe_getenv(const char *n)
{
    if (const char *x = std::getenv(n))
        return x;
    else
        return {};
}

int main()
{
    std::cout << maybe_getenv("SHELL").value_or("(none)") << '\n';
    std::cout << maybe_getenv("MYPWD").value_or("(none)") << '\n';
}
```

---

### **应用场景**

#### 1. **函数返回可能无效的结果**
```cpp
// 查找元素，可能不存在
std::optional<int> find_item(const std::vector<int>& vec, int target) {
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) return *it;
    return std::nullopt;
}

// 使用
auto result = find_item({1, 2, 3}, 2);
if (result) std::cout << "Found: " << *result << std::endl;
```

#### 2. **延迟初始化或可选成员变量**
```cpp
class Config {
public:
    void load() {
        settings_ = read_settings(); // 耗时操作
    }
    // 返回可选配置
    std::optional<Settings> get_settings() const {
        return settings_;
    }
private:
    std::optional<Settings> settings_;
};
```

#### 3. **替代指针或特殊标记值**
```cpp
// 传统方式：使用 -1 表示无效
int parse_number(const std::string& s) {
    try { return std::stoi(s); }
    catch (...) { return -1; } // 歧义：-1 是错误还是有效值？
}

// 使用 std::optional
std::optional<int> safe_parse(const std::string& s) {
    try { return std::stoi(s); }
    catch (...) { return std::nullopt; }
}
```

---

### **高级用法**

#### 1. **链式操作（Monadic 操作，C++23 起）**
C++23 扩展了 `std::optional`，支持类似函数式编程的链式操作：
```cpp
std::optional<int> a = 42;
auto b = a.and_then([](int x) { return x > 0 ? std::optional(x*2) : std::nullopt; });
// b = 84
```

#### 2. **与 `std::variant` 或异常结合**
- 当需要更复杂的错误信息时，`std::variant<std::optional<T>, ErrorCode>` 可能更合适。
- 对于不可恢复的错误，仍建议使用异常。

---

### **注意事项**
1. **性能**：`std::optional<T>` 的大小通常为 `sizeof(T) + 1`（可能因对齐而更大），适合小型对象。
2. **不要滥用**：仅当“无值”是正常逻辑的一部分时使用，若“无值”属于错误，应优先考虑异常。
3. **访问前检查**：直接使用 `*` 或 `->` 前必须确保值存在，否则导致未定义行为。

---

### **总结**
`std::optional` 通过类型安全的方式明确处理“有/无值”的场景，提升代码可读性和健壮性。合理使用可减少对特殊标记或动态内存的依赖，是 C++17 中实用性极高的工具之一。