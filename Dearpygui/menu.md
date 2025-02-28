<!--
 * @Author: feng 1804831168@qq.com
 * @Date: 2025-02-27 21:16:43
 * @LastEditors: feng 1804831168@qq.com
 * @LastEditTime: 2025-02-27 21:18:38
 * @Description: ##
 * Copyright (c) 2025 by Feng, All Rights Reserved.
-->

## 外显分配

属性显式分配父级 父级 关键词。这最常用于在运行时添加新项。下面可以使用显式父级赋值再次显示上面的示例：

```python{}
import dearpygui.dearpygui as dpg

dpg.create_context()

dpg.add_window(label="Tutorial", tag="window")

dpg.add_menu_bar(parent="window", tag="menu_bar")

dpg.add_menu(label="Themes", parent="menu_bar", tag="themes")
dpg.add_menu_item(label="Dark", parent="themes")
dpg.add_menu_item(label="Light", parent="themes")

dpg.create_viewport(title='Custom Title', width=800, height=600)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
```

## 上下文管理器

可以使用上下文管理器来简化上面的示例。所有上下文管理器都可以在 容器和上下文管理器 但下面是一个简单的例子：

```python
import dearpygui.dearpygui as dpg

dpg.create_context()

with dpg.window(label="Tutorial"):
with dpg.menu_bar():
with dpg.menu(label="Themes"):
dpg.add_menu_item(label="Dark")
dpg.add_menu_item(label="Light")
dpg.add_menu_item(label="Classic")

dpg.create_viewport(title='Custom Title', width=800, height=600)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
```

## 视口

```python
import dearpygui.dearpygui as dpg

def print_me(sender):
    print(f"Menu Item: {sender}")

dpg.create_context()
dpg.create_viewport(title='Custom Title', width=600, height=200)

with dpg.viewport_menu_bar():
    with dpg.menu(label="File"):
        dpg.add_menu_item(label="Save", callback=print_me)
        dpg.add_menu_item(label="Save As", callback=print_me)

        with dpg.menu(label="Settings"):
            dpg.add_menu_item(label="Setting 1", callback=print_me, check=True)
            dpg.add_menu_item(label="Setting 2", callback=print_me)

    dpg.add_menu_item(label="Help", callback=print_me)

    with dpg.menu(label="Widget Items"):
        dpg.add_checkbox(label="Pick Me", callback=print_me)
        dpg.add_button(label="Press Me", callback=print_me)
        dpg.add_color_picker(label="Color Me", callback=print_me)

dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
```
