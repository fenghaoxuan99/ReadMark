

从概念上来说，constexpr表明一个值不仅仅是常量，还是编译期可知的。
当constexpr被用于函数的时候，有一些细微差别。
不能假设constexpr函数的结果是const，也不能保证它们的返回值是在编译期可知的。最有意思的是，这些是特性。关于constexpr函数返回的结果不需要是const，也不需要编译期可知这一点是良好的行为！


1. **编译时常量**：`constexpr` 可以用于定义编译时常量，这些常量必须在编译时就能确定其值，例如：
   ```cpp
   constexpr int daysInWeek = 7;
   ```

2. **编译时求值的函数**：`constexpr` 函数是指可以在编译时求值的函数，其返回类型和参数类型都必须是字面类型（literal types），例如：
   ```cpp
   constexpr int add(int a, int b) {
       return a + b;
   }
   ```

3. **模板参数**：`constexpr` 可以作为模板参数，允许模板在编译时进行更多的优化和错误检查：
   ```cpp
   template<constexpr int N>
   void printNTimes() {
       for (int i = 0; i < N; ++i) {
           std::cout << "Hello, World!" << std::endl;
       }
   }
   ```

4. **常量表达式**：`constexpr` 可以用于定义常量表达式，这些表达式可以在编译时求值，并且可以用于数组的大小、枚举值等：
   ```cpp
   constexpr int arraySize = 10;
   int myArray[arraySize]; // 使用 constexpr 定义的数组大小
   ```

5. **提高性能**：使用 `constexpr` 可以减少运行时的计算，因为编译器可以在编译时就计算出结果，从而提高程序的执行效率。

6. **错误检查**：`constexpr` 还可以帮助编译器在编译时进行更多的错误检查，如果 `constexpr` 变量或函数的实现不能在编译时求值，编译器将报错。

7. **类和对象**：从 C++14 开始，`constexpr` 也可以用于类和对象，这意味着你可以创建在编译时构造的对象，并且可以在编译时调用它们的成员函数：


   ```cpp
   constexpr int value = 42;
   struct Foo {
       constexpr int getValue() const { return value; }
   };
   constexpr Foo foo;
   static_assert(foo.getValue() == 42, "Value must be 42");
   ```

8. **标准库中的使用**：许多标准库中的函数和类都使用了 `constexpr`，例如 `std::array`、`std::tuple` 等，这使得它们可以在编译时进行更多的操作。
