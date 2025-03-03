## 在 Dear PyGui (DPG) 中，`dpg.push_container_stack()` 和 `dpg.pop_container_stack()` 是用于管理 UI 容器层级关系的重要函数。

### **功能概述**

这对函数用于管理 **容器堆栈**，实现 UI 元素的 **自动化层级嵌套**。通过它们可以：

1. 临时指定父容器作用域
2. 简化嵌套 UI 的创建流程
3. 避免重复指定 `parent` 参数

---

### **函数详解**

#### **1. dpg.push_container_stack(container)**

| 参数        | 类型    | 说明                             |
| ----------- | ------- | -------------------------------- |
| `container` | str/int | 要设置为当前父容器的 UI 元素标识 |

**作用**：  
将指定容器推入堆栈顶部，后续创建的 UI 元素会自动成为该容器的子元素。

#### **2. dpg.pop_container_stack()**

**作用**：  
弹出堆栈顶部的容器，恢复前一个父容器状态（无参数）

---

### **核心机制**

- 维护一个 **后进先出 (LIFO)** 的容器堆栈
- 创建新 UI 元素时，自动使用栈顶容器作为父级
- 典型应用场景：窗口 > 子容器 > 控件 的多级嵌套

---

### **使用示例**

```python
import dearpygui.dearpygui as dpg

dpg.create_context()

with dpg.window(label="Main Window"):
    # 推入第一个容器（Group A）
    dpg.push_container_stack(dpg.add_group(label="Group A"))

    dpg.add_text("This text is in Group A")
    dpg.add_button(label="Button in Group A")

    # 推入第二个容器（Subgroup）
    dpg.push_container_stack(dpg.add_group(label="Subgroup"))
    dpg.add_text("Nested in Subgroup")
    dpg.add_slider_float(label="Slider")

    # 弹出回到 Group A
    dpg.pop_container_stack()

    # 继续在 Group A 添加元素
    dpg.add_checkbox(label="Checkbox")

    # 弹出回到 Main Window
    dpg.pop_container_stack()

dpg.create_viewport()
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
```

---

### **关键特性**

1. **自动继承**：

   ```python
   # 不需要显式指定 parent 参数
   dpg.add_text("Auto-parented to current stack top")
   ```

2. **嵌套深度**：

   ```python
   # 支持任意深度嵌套
   dpg.push_container_stack(container1)
   dpg.push_container_stack(container2)
   dpg.push_container_stack(container3)
   # 创建属于 container3 的元素
   dpg.pop_container_stack()  # 回到 container2
   dpg.pop_container_stack()  # 回到 container1
   ```

3. **混合使用**：
   ```python
   # 可以与显式 parent 参数结合使用
   dpg.add_button(
       label="Hybrid Usage",
       parent=dpg.add_group()  # 显式指定父级
   )
   ```

---

### **典型应用场景**

1. **动态界面构建**：

   ```python
   def build_section():
       with dpg.group() as section:
           dpg.push_container_stack(section)
           # 构建复杂子元素
           dpg.pop_container_stack()
   ```

2. **模板化组件**：

   ```python
   def create_card(title):
       with dpg.group() as card:
           dpg.push_container_stack(card)
           dpg.add_text(title)
           dpg.add_separator()
           # 添加卡片内容...
           dpg.pop_container_stack()
       return card
   ```

3. **临时容器切换**：

   ```python
   with dpg.window(label="Editor"):
       main_group = dpg.add_group()

       # 临时切换到工具栏
       dpg.push_container_stack(toolbar_group)
       dpg.add_button(label="Save")
       dpg.add_button(label="Load")
       dpg.pop_container_stack()

       # 继续在 main_group 工作
       dpg.push_container_stack(main_group)
       # ...
   ```

---

### **注意事项**

1. **堆栈平衡**：

   ```python
   # 必须确保 push/pop 成对出现
   try:
       dpg.push_container_stack(container)
       # ... 操作 ...
   finally:
       dpg.pop_container_stack()  # 确保始终执行
   ```

2. **性能优化**：

   ```python
   # 对频繁更新的 UI 部分建议：
   - 保持堆栈层级扁平化
   - 避免深度嵌套 (>5 层)
   ```

3. **调试技巧**：
   ```python
   # 查看当前堆栈状态
   print(dpg.get_container_stack())
   ```

---

通过合理使用容器堆栈管理，可以显著提升复杂 UI 布局的可维护性和代码简洁度。
