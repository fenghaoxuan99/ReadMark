

`constexpr` 是 C++11 引入的关键字，用于指示编译器在编译时求值，从而优化性能并支持编译时计算。以下是其详细用法和用途：

---

### **1. 核心概念**
- **编译时常量**：`constexpr` 声明的变量或函数返回值必须在编译时确定，可直接用于需要常量的场景（如数组大小、模板参数等）。
- **与 `const` 的区别**：`const` 变量可以是运行时常量，而 `constexpr` 必须是编译时常量。

---

### **2. 用法分类**

#### **（1）`constexpr` 变量**
- **规则**：必须用常量表达式初始化。
- **示例**：
  ```cpp
  constexpr int x = 10;                  // 正确，字面量是常量表达式
  constexpr int y = x + 5;               // 正确，x是编译时常量
  // constexpr int z = std::rand();      // 错误：std::rand() 是运行时函数
  ```

#### **（2）`constexpr` 函数**
- **规则**：
  - C++11：函数体仅能包含一条 `return` 语句，不支持循环/局部变量。
  - C++14+：允许局部变量、循环、条件语句等，但所有路径必须可编译时求值。
- **示例**（C++14）：
  ```cpp
  constexpr int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) result *= i;
    return result;
  }
  constexpr int fact_5 = factorial(5);  // 编译时计算 120
  ```

#### **（3）`constexpr` 构造函数与对象**
- **规则**：
  - 构造函数体必须为空，所有成员需用常量表达式初始化。
  - 成员函数可标记为 `constexpr`，用于编译时操作。
- **示例**：
  ```cpp
  class Point {
  public:
    constexpr Point(int x, int y) : x_(x), y_(y) {}
    constexpr int x() const { return x_; }
    constexpr int y() const { return y_; }
  private:
    int x_, y_;
  };
  constexpr Point p(3, 4);              // 编译时创建对象
  constexpr int px = p.x();             // 编译时访问成员
  ```

---

### **3. 主要用途**
- **性能优化**：将计算移至编译期，减少运行时开销。
- **类型安全**：编译时验证常量值，避免运行时错误。
- **模板元编程**：结合模板实现编译时算法（如类型列表操作）。
- **条件编译**：C++17 的 `if constexpr` 简化模板代码分支选择。

---

### **4. 版本差异**
| 特性                | C++11                      | C++14+                     |
|---------------------|----------------------------|----------------------------|
| 函数体复杂度        | 仅单行 `return`            | 支持循环、局部变量等       |
| `constexpr` 成员函数 | 不支持                     | 支持                       |
| `constexpr` 变量     | 支持基本类型和自定义类型   | 增强对自定义类型的支持     |

---

### **5. 注意事项**
- **依赖项限制**：`constexpr` 函数内部只能调用其他 `constexpr` 函数或字面量。
- **隐式内联**：`constexpr` 函数默认内联，建议放在头文件中。
- **错误处理**：若 `constexpr` 函数在运行时调用且包含非法操作（如未定义行为），可能导致编译失败或运行时错误。

---

### **6. 示例场景**
- **编译时计算数组大小**：
  ```cpp
  constexpr int calc_size(int n) { return n * 2; }
  int arr[calc_size(10)];  // 合法，数组大小为 20
  ```
- **模板元编程**：
  ```cpp
  template<int N>
  struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
  };
  template<>
  struct Factorial<0> { static constexpr int value = 1; };
  constexpr int fact = Factorial<5>::value;  // 120
  ```
- **C++17 `if constexpr`**：
  ```cpp
  template<typename T>
  auto print_type(const T&) {
    if constexpr (std::is_integral_v<T>) {
      return "Integer";
    } else {
      return "Other";
    }
  }
  ```

---

### **总结**
`constexpr` 通过将计算移至编译期，提升了程序的性能和类型安全性。合理使用可优化代码结构，但需注意不同版本的语法限制和依赖项的编译时常量化。