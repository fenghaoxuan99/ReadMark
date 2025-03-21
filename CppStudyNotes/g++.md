

`g++` 是 GNU Compiler Collection (GCC) 中的 C++ 编译器，用于将 C++ 源代码编译成可执行文件或库。以下是 `g++` 的常见用法及详细说明，涵盖从基础到高级的功能。

---

### **一、基本用法**
#### 1. 编译单个源文件
```bash
g++ main.cpp -o output
```
- **说明**：将 `main.cpp` 编译成名为 `output` 的可执行文件。
- **参数**：
  - `main.cpp`：输入的 C++ 源文件。
  - `-o output`：指定输出文件名（默认为 `a.out`）。

---

#### 2. 编译多个源文件
```bash
g++ main.cpp utils.cpp -o program
```
- **说明**：将 `main.cpp` 和 `utils.cpp` 一起编译并链接成 `program`。

---

### **二、常用编译选项**
#### 1. 优化级别
```bash
g++ -O0 main.cpp   # 无优化（默认，适合调试）
g++ -O1 main.cpp   # 基本优化
g++ -O2 main.cpp   # 更高级优化（推荐发布时使用）
g++ -O3 main.cpp   # 激进优化（可能增加代码体积）
```
- **说明**：`-O` 后接数字指定优化级别，级别越高性能越好，但编译时间更长。

---

#### 2. 生成调试信息
```bash
g++ -g main.cpp -o debug_program
```
- **说明**：添加调试信息（供 `gdb` 调试器使用）。

---

#### 3. 启用所有警告
```bash
g++ -Wall -Wextra -pedantic main.cpp
```
- **参数**：
  - `-Wall`：启用常见警告（如未使用变量）。
  - `-Wextra`：额外警告（如未初始化的变量）。
  - `-pedantic`：严格遵循 ISO C++ 标准。

---

#### 4. 指定 C++ 标准
```bash
g++ -std=c++11 main.cpp    # C++11
g++ -std=c++14 main.cpp    # C++14
g++ -std=c++17 main.cpp    # C++17
g++ -std=c++20 main.cpp    # C++20
```
- **说明**：指定使用的 C++ 标准版本。

---

#### 5. 生成预处理文件
```bash
g++ -E main.cpp > main.ii
```
- **说明**：仅执行预处理，生成展开宏和头文件后的代码（`.ii` 文件）。

---

#### 6. 生成汇编代码
```bash
g++ -S main.cpp    # 生成 main.s（汇编文件）
```

---

#### 7. 生成目标文件（不链接）
```bash
g++ -c main.cpp    # 生成 main.o
```
- **用途**：分步编译多个文件，最后再链接。

---

### **三、链接选项**
#### 1. 链接静态库
```bash
g++ main.cpp libmath.a -o program
```
- **说明**：链接名为 `libmath.a` 的静态库。

---

#### 2. 链接动态库
```bash
g++ main.cpp -lmath -L/path/to/libs -o program
```
- **参数**：
  - `-lmath`：链接名为 `libmath.so`（Linux）或 `libmath.dylib`（macOS）的动态库。
  - `-L/path/to/libs`：指定库文件的搜索路径。

---

#### 3. 指定头文件路径
```bash
g++ -I/path/to/headers main.cpp
```
- **说明**：添加自定义头文件搜索路径。

---

### **四、生成静态库和动态库**
#### 1. 生成静态库
```bash
# 1. 编译目标文件
g++ -c utils.cpp
# 2. 打包成静态库
ar rcs libutils.a utils.o
```
- **使用静态库**：
  ```bash
  g++ main.cpp -L. -lutils -o program
  ```

---

#### 2. 生成动态库（共享库）
```bash
# 1. 编译为目标文件（需生成位置无关代码）
g++ -c -fPIC utils.cpp
# 2. 生成动态库
g++ -shared -o libutils.so utils.o
```
- **使用动态库**：
  ```bash
  g++ main.cpp -L. -lutils -o program
  ```
- **运行前**：确保系统能找到动态库（可通过 `export LD_LIBRARY_PATH=.` 临时添加路径）。

---

### **五、高级用法**
#### 1. 宏定义
```bash
g++ -DDEBUG main.cpp    # 定义宏 DEBUG
g++ -DNAME=value main.cpp  # 定义带值的宏
```

---

#### 2. 生成依赖文件（用于 Makefile）
```bash
g++ -M main.cpp     # 输出依赖关系（包含系统头文件）
g++ -MM main.cpp    # 忽略系统头文件
```

---

#### 3. 指定输出文件名
```bash
g++ main.cpp -o custom_name
```

---

#### 4. 启用 C++ RTTI（运行时类型信息）
```bash
g++ -frtti main.cpp    # 默认启用
g++ -fno-rtti main.cpp # 禁用
```

---

### **六、其他实用命令**
#### 1. 查看编译器版本
```bash
g++ --version
```

---

#### 2. 显示详细的编译过程
```bash
g++ -v main.cpp
```

---

#### 3. 指定语言标准兼容模式
```bash
g++ -ansi main.cpp    # 严格遵循 ISO C++ 标准
```

---

### **七、典型编译流程示例**
1. **预处理**：展开宏和头文件。
2. **编译**：生成汇编代码（`.s` 文件）。
3. **汇编**：生成目标文件（`.o` 文件）。
4. **链接**：将目标文件和库链接成可执行文件。

---

### **八、总结**
- **调试阶段**：使用 `-g -O0 -Wall` 确保代码可调试且无警告。
- **发布阶段**：使用 `-O2` 或 `-O3` 优化性能。
- **多文件项目**：分步编译目标文件，最后链接。

通过灵活组合这些选项，可以高效管理 C++ 项目的编译和优化。