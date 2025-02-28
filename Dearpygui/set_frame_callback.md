---

### `dpg.set_frame_callback()` 函数详解

`dpg.set_frame_callback()` 是 Dear PyGui 中用于**按帧调度回调函数**的核心接口，其核心作用是在指定的绝对帧数触发自定义函数。理解其参数和机制对实现动画、实时数据更新等功能至关重要。

---

#### **函数签名**

```python
dpg.set_frame_callback(frame_number: int, callback: Callable)
```

---

### **参数详解**

| 参数           | 类型       | 意义                                                       |
| -------------- | ---------- | ---------------------------------------------------------- |
| `frame_number` | `int`      | **绝对帧数**：希望触发回调的目标帧编号（必须 ≥ 当前帧数）  |
| `callback`     | `Callable` | 回调函数：当程序运行到 `frame_number` 帧时，自动执行此函数 |

---

### **关键特性**

1. **绝对帧数机制**  
   Dear PyGui 内部维护一个全局帧计数器（可通过 `dpg.get_frame_count()` 获取）。

   - 若 `frame_number` ≤ 当前帧数，回调会立即执行（但可能导致逻辑混乱）。
   - 若 `frame_number` 为未来帧，回调将在程序运行到该帧时触发。

2. **单次触发**  
   每个 `set_frame_callback` 调用仅注册一次回调。若需持续触发，需在回调内重新注册。

3. **执行顺序**  
   同一帧注册的多个回调按注册顺序执行。

---

### **典型用途**

| 场景               | 代码示例                                    |
| ------------------ | ------------------------------------------- |
| **延迟初始化**     | `dpg.set_frame_callback(3, init_resources)` |
| **周期性数据更新** | 在回调中重新注册自身（见下方示例）          |
| **动画关键帧控制** | 在不同帧注册多个回调实现复杂动画序列        |

---

### **正确用法示例**

```python
def update_data():
    # 更新数据的逻辑...
    # 注册下一帧回调（关键！）
    next_frame = dpg.get_frame_count() + 1
    dpg.set_frame_callback(next_frame, update_data)

# 初始启动：在第5帧开始更新
dpg.set_frame_callback(5, update_data)
```

---

### **常见错误与注意事项**

1. **错误：使用相对帧增量**

   ```python
   # 错误！frame_count 是递增变量，可能注册到过去的帧
   dpg.set_frame_callback(frame_count, callback)
   ```

   **修正**：始终基于当前帧计算绝对帧数：

   ```python
   next_frame = dpg.get_frame_count() + 1
   ```

2. **错误：未重新注册导致只执行一次**  
   若需持续更新，必须在回调内部重新注册下一帧：

   ```python
   def update():
       # ...更新逻辑...
       dpg.set_frame_callback(dpg.get_frame_count() + 1, update)  # 重新注册
   ```

3. **性能陷阱**

   - 避免每帧注册高开销回调（如密集计算）。可通过模运算降低频率：
     ```python
     if dpg.get_frame_count() % 5 == 0:  # 每5帧更新一次
         update_data()
     ```

4. **帧号溢出**  
   Dear PyGui 的帧计数器为 `int` 类型，理论上不会溢出。但长期运行的程序应定期重置逻辑帧号。

---

### **调试技巧**

1. **打印帧信息**

   ```python
   def callback():
       print(f"Frame {dpg.get_frame_count()}: Callback triggered")
   ```

2. **可视化帧计数器**
   ```python
   dpg.add_text("Current Frame: ", tag="frame_text")
   def update_frame_text():
       dpg.set_value("frame_text", f"Current Frame: {dpg.get_frame_count()}")
   dpg.set_frame_callback(dpg.get_frame_count() + 1, update_frame_text)
   ```

---

### **与其他定时机制对比**

| 方法                   | 精度     | 适用场景                         |
| ---------------------- | -------- | -------------------------------- |
| `set_frame_callback()` | 帧级精确 | 动画、实时数据同步               |
| `add_tick_callback()`  | 每帧执行 | 需要每帧更新的逻辑（如物理模拟） |
| `PyTimer` (threading)  | 毫秒级   | 后台任务、I/O 操作               |

---

掌握 `set_frame_callback()` 的绝对帧数机制和重新注册模式，可高效实现 Dear PyGui 的动态交互功能。关键点总结：**始终基于 `dpg.get_frame_count()` 计算未来帧，并在回调内重新注册以持续运行**。

```python
import dearpygui.dearpygui as dpg
import random

frame_count = 0
x_data = []
y_data = []
running = True


def update_data():
    global frame_count, x_data, y_data
    if not running:
        return

    if frame_count % 5 == 0:  # 控制刷新率为1/5帧
        new_x = len(x_data)
        new_y = random.randint(0, 100)
        x_data.append(new_x)
        y_data.append(new_y)

        if len(x_data) > 200:
            x_data = x_data[-200:]
            y_data = y_data[-200:]

        dpg.set_value("series", [x_data, y_data])
        dpg.fit_axis_data("x_axis")
        dpg.fit_axis_data("y_axis")

    frame_count += 1
    # 注册下一帧回调（关键修正）
    dpg.set_frame_callback(dpg.get_frame_count() + 1, update_data)


def toggle_update():
    global running

    running = not running
    dpg.set_frame_callback(dpg.get_frame_count() + 1, update_data)


dpg.create_context()

with dpg.window(label="实时曲线", tag="main_window"):
    with dpg.plot(label="数据曲线", height=400, width=800):
        dpg.add_plot_axis(dpg.mvXAxis, label="Index", tag="x_axis")
        y_axis = dpg.add_plot_axis(dpg.mvYAxis, label="Value", tag="y_axis")
        dpg.add_line_series([], [], parent=y_axis, tag="series", label="随机数据")

        # 将按钮添加到绘图区域的子容器中
    with dpg.group(horizontal=True):
        dpg.add_button(label="暂停/继续", callback=toggle_update)

dpg.set_primary_window("main_window", True)
dpg.set_frame_callback(5, update_data)  # 初始启动

dpg.create_viewport(title='实时数据监控', width=850, height=500)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
```
