在 Dear PyGui 中，`dpg.configure_item()` 是一个核心函数，用于动态修改已创建 GUI 项的属性。其用法和参数高度依赖于目标项的类型，以下是一些常见用法和参数分类说明：

---

### **通用参数（多数组件支持）**

| 参数             | 适用组件       | 说明                         |
| ---------------- | -------------- | ---------------------------- |
| `show`           | 所有可见项     | 控制显示/隐藏 (`True/False`) |
| `enabled`        | 按钮/输入项等  | 启用或禁用交互性             |
| `label`          | 带标签的项     | 修改显示标签                 |
| `width`/`height` | 可调整大小的项 | 设置尺寸（像素）             |
| `pos`            | 可定位项       | 设置位置坐标 `[x, y]`        |
| `parent`         | 有父级关系的项 | 动态更换父容器               |
| `user_data`      | 所有项         | 附加自定义数据               |

---

### **按组件类型分类的关键参数**

#### **窗口 (window)**

```python
dpg.configure_item("window_id",
    title="新标题",
    no_close=True,  # 禁用关闭按钮
    autosize=True,
    collapsed=True  # 折叠窗口
)
```

#### **按钮/交互项**

```python
dpg.configure_item("btn_id",
    callback=new_callback,  # 更换回调函数
    enabled=False  # 禁用按钮
)
```

#### **输入组件 (input\_\*)**

```python
# 输入框 (input_text)
dpg.configure_item("input_id",
    default_value="新文本",
    multiline=True,  # 允许多行
    password=True    # 密码模式
)

# 滑动条 (slider_*)
dpg.configure_item("slider_id",
    min_value=0, max_value=100,
    format="%.2f"  # 数值格式
)
```

#### **绘图/图表 (plot)**

```python
dpg.configure_item("plot_id",
    x_axis_limits=[0, 10],  # 设置X轴范围
    y_axis_limits=[-5, 5],
    no_legend=False  # 显示图例
)
```

#### **表格 (table)**

```python
dpg.configure_item("table_id",
    header_row=True,  # 显示表头
    resizable=True,   # 允许调整列宽
    policy=dpg.mvTable_SizingStretchProp  # 自适应策略
)
```

#### **树节点 (tree_node)**

```python
dpg.configure_item("tree_id",
    default_open=True  # 默认展开节点
)
```

---

### **样式相关参数**

```python
# 颜色设置（支持多种格式）
dpg.configure_item("item_id", color=(255,0,0,255))  # RGBA元组
dpg.configure_item("item_id", color="#FF0000")      # 十六进制

# 字体
dpg.configure_item("text_id", font="custom_font_id")

# 边框/圆角
dpg.configure_item("btn_id", frame_rounding=5)
```

---

### **高级用法示例**

1. **动态更新绘图数据**

   ```python
   dpg.configure_item("line_series_id", x=new_x_data, y=new_y_data)
   ```

2. **切换主题**

   ```python
   dpg.configure_item("window_id", theme="dark_theme_id")
   ```

3. **修改菜单项**
   ```python
   dpg.configure_item("menu_item_id", shortcut="Ctrl+S", check=True)
   ```

---

### **查看完整参数的技巧**

1. **官方文档**：访问 [Dear PyGui 文档](https://dearpygui.readthedocs.io/)，搜索对应组件的 `configure` 方法。
2. **上下文帮助**：在代码编辑器中输入 `dpg.configure_item(` 时，IDE 的自动补全功能会显示可用参数。
3. **运行时打印**：使用 `dpg.get_item_configuration(item_id)` 查看当前配置。

建议根据具体组件类型查阅对应文档，因为不同控件可能有专属参数（如 `mvPlot` 的轴标签设置、`mvImage` 的像素数据更新等）。
