

`std::variant` 是 C++17 引入的一个模板类，用于表示一个类型安全的联合体（union）。它可以存储多种预定义类型中的一种，并在运行时安全地访问存储的值。与传统的联合体（`union`）相比，`std::variant` 支持非平凡类型（如 `std::string`），且提供类型安全的访问机制。

---

### **核心用途**
1. **替代传统联合体**：传统的 `union` 无法直接存储非平凡类型（如带有构造函数的对象），而 `std::variant` 可以。
2. **类型安全的多种可能值**：适用于需要存储多种类型但每次只能使用一种的场景（如解析 JSON、错误处理、状态机等）。
3. **避免动态内存分配**：与 `std::any` 不同，`std::variant` 在编译时确定可能的类型，无需运行时类型信息（RTTI），更高效。

---

### **基本用法**
#### 1. **包含头文件与定义**
```cpp
#include <variant>
#include <string>

// 定义一个 variant，可存储 int、double 或 std::string
std::variant<int, double, std::string> myVariant;
```

#### 2. **赋值与初始化**
```cpp
myVariant = 42;                // 存储 int
myVariant = 3.14;              // 存储 double
myVariant = "Hello, variant!"; // 存储 std::string
```

#### 3. **访问值**
- **`std::get<T>()` 或 `std::get<Index>()`**  
  直接获取存储的值，若类型不匹配或索引错误，抛出 `std::bad_variant_access`。
  ```cpp
  auto intValue = std::get<int>(myVariant);       // 按类型访问
  auto strValue = std::get<2>(myVariant);         // 按索引访问（索引从 0 开始）
  ```

- **`std::get_if<T>()`**  
  安全地获取指针，若类型不匹配返回 `nullptr`。
  ```cpp
  if (auto* p = std::get_if<double>(&myVariant)) {
      std::cout << "Double value: " << *p << std::endl;
  }
  ```

- **`std::visit()`**  
```cpp
template< class Visitor, class... Variants >
constexpr /* see below */ visit( Visitor&& v, Variants&&... values );
```
第一个参数是可调用的对象，第二个是参数。
  使用访问者模式处理所有可能的类型。
  ```cpp
  std::visit([](auto&& arg) {
      using T = std::decay_t<decltype(arg)>;
      if constexpr (std::is_same_v<T, int>) {
          std::cout << "int: " << arg << std::endl;
      } else if constexpr (std::is_same_v<T, double>) {
          std::cout << "double: " << arg << std::endl;
      } else if constexpr (std::is_same_v<T, std::string>) {
          std::cout << "string: " << arg << std::endl;
      }
  }, myVariant);
  ```

#### 4. **检查当前类型**
- **`index()`**：返回当前存储类型的索引（从 0 开始）。
  ```cpp
  if (myVariant.index() == 0) {
      std::cout << "Currently holds an int." << std::endl;
  }
  ```

- **`std::holds_alternative<T>()`**：检查是否存储了特定类型。
  ```cpp
  if (std::holds_alternative<std::string>(myVariant)) {
      std::cout << "Holds a string." << std::endl;
  }
  ```

---

### **高级用法**
#### 1. **默认初始化**
- `std::variant` 默认初始化为第一个类型的默认值。  
  若第一个类型无默认构造函数，需显式初始化：
  ```cpp
  struct NonDefaultConstructible {
      NonDefaultConstructible(int) {}
  };
  std::variant<NonDefaultConstructible, int> v{std::in_place_index<1>, 42}; // 显式初始化
  ```

#### 2. **就地构造 (`emplace`)**
直接构造对象，避免临时变量：
emplace<2> 也可是 emplace<string>
```cpp
myVariant.emplace<2>("Construct in-place"); // 在索引 2 的位置构造 std::string
```

#### 3. **`std::monostate` 表示空状态**
默认情况下，`std::variant` 不能为空。若需要空状态，可包含 `std::monostate`：
```cpp
std::variant<std::monostate, int, std::string> v;
if (v.index() == 0) {
    std::cout << "Variant is empty." << std::endl;
}
```

---

### **示例场景**
#### 错误处理
```cpp
std::variant<int, std::string> parseInput(const std::string& input) {
    try {
        return std::stoi(input);
    } catch (...) {
        return "Invalid input";
    }
}

auto result = parseInput("123");
if (std::holds_alternative<int>(result)) {
    std::cout << "Parsed value: " << std::get<int>(result) << std::endl;
} else {
    std::cerr << std::get<std::string>(result) << std::endl;
}
```

---

### **与 `std::any` 的区别**
| 特性                | `std::variant`                  | `std::any`                      |
|---------------------|----------------------------------|----------------------------------|
| 类型确定时间        | 编译时（需预定义类型列表）       | 运行时（可存储任意类型）         |
| 性能                | 更高（无动态内存分配）           | 较低（可能涉及动态分配）         |
| 类型安全            | 是                               | 是（但需显式类型转换）           |

---

### **总结**
- **何时使用 `std::variant`**：当需要存储一组预定义类型中的一种，且需类型安全和高效访问时。
- **优点**：类型安全、支持非平凡类型、无额外内存开销。
- **注意**：避免重复类型（如 `variant<int, int>`）和确保访问时类型匹配。

通过 `std::variant`，C++ 提供了一种现代、安全的方式处理多类型数据，替代了传统的 `union` 和繁琐的类型检查逻辑。