<!--
 * @Author: feng 1804831168@qq.com
 * @Date: 2025-02-27 21:18:15
 * @LastEditors: feng 1804831168@qq.com
 * @LastEditTime: 2025-03-03 11:13:09
 * @Description:
 * Copyright (c) 2025 by Feng, All Rights Reserved.
-->

## drawlist 基本用法

```python
import dearpygui.dearpygui as dpg

dpg.create_context()

with dpg.window(label="Tutorial"):

    with dpg.drawlist(width=300, height=300):  # or you could use dpg.add_drawlist and set parents manually

        dpg.draw_line((10, 10), (100, 100), color=(255, 0, 0, 255), thickness=1)
        dpg.draw_text((0, 0), "Origin", color=(250, 250, 250, 255), size=15)
        dpg.draw_arrow((50, 70), (100, 65), color=(0, 200, 255), thickness=1, size=10)

dpg.create_viewport(title='Custom Title', width=800, height=600)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
```

## draw_layer

```python
import dearpygui.dearpygui as dpg

dpg.create_context()

def toggle_layer2(sender):
    show_value = dpg.get_value(sender)
    dpg.configure_item("layer2", show=show_value)

with dpg.window(label="Tutorial"):
    dpg.add_checkbox(label="show layer", callback=toggle_layer2, default_value=True)

    with dpg.drawlist(width=300, height=300):

        with dpg.draw_layer():
            dpg.draw_line((10, 10), (100, 100), color=(255, 0, 0, 255), thickness=1)
            dpg.draw_text((0, 0), "Origin", color=(250, 250, 250, 255), size=15)
            dpg.draw_arrow((50, 70), (100, 65), color=(0, 200, 255), thickness=1, size=10)

        with dpg.draw_layer(tag="layer2"):
            dpg.draw_line((10, 60), (100, 160), color=(255, 0, 0, 255), thickness=1)
            dpg.draw_arrow((50, 120), (100, 115), color=(0, 200, 255), thickness=1, size=10)

dpg.create_viewport(title='Custom Title', width=800, height=600)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
```

## 图像

```python
import dearpygui.dearpygui as dpg

dpg.create_context()

width, height, channels, data = dpg.load_image('SpriteMapExample.png') # 0: width, 1: height, 2: channels, 3: data

with dpg.texture_registry():
    dpg.add_static_texture(width, height, data, tag="image_id")

with dpg.window(label="Tutorial"):

    with dpg.drawlist(width=700, height=700):

        dpg.draw_image("image_id", (0, 400), (200, 600), uv_min=(0, 0), uv_max=(1, 1))
        dpg.draw_image("image_id", (400, 300), (600, 500), uv_min=(0, 0), uv_max=(0.5, 0.5))
        dpg.draw_image("image_id", (0, 0), (300, 300), uv_min=(0, 0), uv_max=(2.5, 2.5))

dpg.create_viewport(title='Custom Title', width=800, height=600)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
```

## Viewport

可以使用 viewport_Drawlist 绘制到视区前景或背景。

```python
import dearpygui.dearpygui as dpg

dpg.create_context()

# creating font and back viewport drawlists
with dpg.viewport_drawlist():
    dpg.draw_circle((100, 100), 25, color=(255, 255, 255, 255))

dpg.add_viewport_drawlist(front=False, tag="viewport_back")

dpg.draw_circle((200, 200), 25, color=(255, 255, 255, 255), parent="viewport_back")

with dpg.window(label="Tutorial", width=300, height=300):
    dpg.add_text("Move the window over the drawings to see the effects.", wrap=300)
    dpg.draw_circle((100, 100), 25, color=(255, 255, 255, 255))

dpg.create_viewport(title='Custom Title', width=800, height=600)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
```

以下是关于 `dpg.draw_image` 函数的参数详解：

---

### **函数原型**

```python
dpg.draw_image(
    texture_id,      # 纹理标识符
    pmin,            # 绘制区域起点坐标
    pmax,            # 绘制区域终点坐标
    uv_min=(0,0),    # 纹理采样起点 (归一化坐标)
    uv_max=(1,1),    # 纹理采样终点 (归一化坐标)
    **kwargs         # 其他绘制参数
)
```

---

### **参数详解**

#### **1. `texture_id`**

- **类型**：`str/int`
- **作用**：通过 `add_static_texture` 注册的纹理标识符
- **获取方式**：
  ```python
  # 先加载纹理
  width, height, channels, data = dpg.load_image("image.png")
  texture_id = dpg.add_static_texture(width, height, data)
  ```

#### **2. `pmin`**

- **类型**：`tuple (x1, y1)`
- **坐标系**：视口左下角为原点 (0,0)，右上角为 (viewport_width, viewport_height)
- **作用**：定义绘制矩形的 **左下角** 坐标
- **示例**：
  ```python
  (0, 0)    # 视口左下角
  (100,200) # 向右100像素，向上200像素的位置
  ```

#### **3. `pmax`**

- **类型**：`tuple (x2, y2)`
- **作用**：定义绘制矩形的 **右上角** 坐标
- **实际尺寸计算**：
  ```python
  宽度 = x2 - x1
  高度 = y2 - y1
  ```
- **示例组合**：
  ```python
  pmin=(0,400), pmax=(200,600)
  # 绘制区域：宽200px，高200px
  # 位置：从视口左边缘开始，垂直方向400px到600px之间
  ```

#### **4. `uv_min`**

- **类型**：`tuple (u1, v1)`
- **范围**：`[0.0, 1.0]` 的归一化坐标
- **作用**：指定纹理采样的 **起始点**
- **坐标系**：
  - `u` 轴：纹理水平方向（0=左，1=右）
  - `v` 轴：纹理垂直方向（0=下，1=上）
- **示例**：
  ```python
  uv_min=(0.2, 0.3)  # 从纹理宽度20%处，高度30%处开始采样
  ```

#### **5. `uv_max`**

- **类型**：`tuple (u2, v2)`
- **作用**：指定纹理采样的 **结束点**
- **组合效果**：
  ```python
  uv_min=(0.2,0.3), uv_max=(0.8,0.7)
  # 实际采样区域：纹理中间60%宽度，中间40%高度
  ```

---

### **关键特性图示**

```
视口坐标系 (pmin/pmax)
+------------------> X
|(0,0)
|  +---------------+
|  | 纹理采样区域  |
|  | (uv_min~uv_max)|
V  +---------------+
Y             (viewport_height)

纹理坐标系 (uv_min/uv_max)
(0,1) +-----------+
      |           |
      |           |
      +-----------+(1,0)
```

---

### **完整使用示例**

```python
import dearpygui.dearpygui as dpg

dpg.create_context()

# 加载纹理
width, height, channels, data = dpg.load_image("texture.png")
texture_id = dpg.add_static_texture(width, height, data)

with dpg.window(label="Drawing Example"):
    with dpg.drawlist(width=800, height=600):
        dpg.draw_image(
            texture_id,
            pmin=(100, 100),   # 绘制起点
            pmax=(300, 300),   # 绘制终点（实际绘制200x200区域）
            uv_min=(0.25, 0.25),  # 使用纹理中心50%区域
            uv_max=(0.75, 0.75),
            color=(255,255,255,255)  # 颜色混合（可选）
        )

dpg.create_viewport()
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
```

---

### **高级技巧**

1. **动态缩放**：

   ```python
   def update_image():
       current_size = calculate_size()
       dpg.configure_item(
           "draw_command",
           pmin=(0,0),
           pmax=current_size
       )
   ```

2. **纹理切片**：

   ```python
   # 绘制纹理的右半部分
   dpg.draw_image(
       texture_id,
       pmin=(0,0),
       pmax=(200,200),
       uv_min=(0.5,0.0),
       uv_max=(1.0,1.0)
   )
   ```

3. **颜色混合**：
   ```python
   # 添加红色滤镜效果
   dpg.draw_image(
       texture_id,
       pmin=(0,0),
       pmax=(200,200),
       color=(255,100,100,200)  # RGBA
   )
   ```

---

### **常见问题排查**

1. **图像不显示**：

   - 检查纹理是否正确注册
   - 确认 `pmin/pmax` 坐标在可视范围内
   - 验证 UV 坐标是否在 [0,1] 范围内

2. **图像拉伸变形**：

   ```python
   # 保持宽高比计算示例
   tex_aspect = width / height
   draw_width = 300
   draw_height = draw_width / tex_aspect
   pmax = (draw_width, draw_height)
   ```

3. **性能优化**：
   - 对静态图像使用 `add_static_texture`
   - 动态更新的纹理使用 `add_dynamic_texture`
   - 避免每帧重新创建绘制命令
