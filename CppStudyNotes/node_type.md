

在 C++17 中，`node_type` 是标准库中关联容器（如 `map`、`set`、`multimap`、`multiset`）和无序关联容器（如 `unordered_map`、`unordered_set`）引入的一个新特性。它表示容器中的一个节点（即键值对或单个元素）的句柄（handle），允许用户直接操作容器内部的节点，而无需复制或移动元素本身。`node_type` 主要用于高效地转移或修改容器中的元素。

---

### **核心作用**
1. **节点提取和插入**  
   允许从容器中提取（extract）一个节点，然后将其插入到另一个容器中。这种操作避免了元素拷贝或移动，提高了性能。
2. **直接修改键**  
   对于 `map` 和 `set` 等有序容器，键（key）通常是 `const` 的，但通过 `node_type`，可以直接修改节点的键（前提是保证容器的有序性）。
3. **低开销的容器间转移**  
   可以在不同容器之间转移节点（例如从 `map` 转移到 `multimap`）。

---

### **主要成员函数**
`node_type` 提供以下关键操作：
1. **检查有效性**  
   - `bool      empty() const noexcept`：检查节点是否为空。
   - `explicit operator bool() const noexcept`：判断节点是否有效。
2. **访问键和值**  
   - `key_type&       key() const`：获取节点的键（对有序容器，修改键需保证排序不变）。
   - `mapped_type& mapped() const`（仅限 `map` 类型）：获取节点的值。
3. **释放节点所有权**  
   - `void release()`：释放节点所有权，节点变为空。

---

### **基本用法**
#### 1. **提取节点**
使用容器的 `extract` 方法获取节点：
```cpp
std::map<int, std::string> m = {{1, "one"}, {2, "two"}};
auto node = m.extract(1); // 提取键为1的节点
```
- 如果节点不存在，`node` 会为空。

#### 2. **插入节点**
使用容器的 `insert` 方法插入节点：
```cpp
std::map<int, std::string> m2;
m2.insert(std::move(node)); // 插入节点，转移所有权
```
- 插入失败时（如键冲突），节点会返回到原状态。

#### 3. **修改键**
直接修改节点的键（需保证有序性）：
```cpp
std::map<int, std::string> m = {{1, "one"}, {3, "three"}};
auto node = m.extract(1);
node.key() = 2; // 修改键为2
m.insert(std::move(node)); // 插入后，m = {{2, "one"}, {3, "three"}}
```

---

### **容器兼容性**
- **相同容器类型**：节点可以在同类型容器间转移（如 `map` 到 `map`）。
- **不同容器类型**：部分容器支持跨类型转移，例如：
  - `map` 的节点可以插入到 `multimap`（允许重复键）。
  - `set` 的节点可以插入到 `multiset`。
  - 但反向操作（如 `multimap` 到 `map`）可能失败（如果键重复）。

---

### **注意事项**
1. **节点有效性**  
   提取节点后，原容器中的元素被移除，节点句柄拥有该元素的唯一所有权。
2. **键修改限制**  
   修改键时需确保容器有序性（例如对 `map` 修改后的键不能与其他键冲突）。
3. **性能优势**  
   节点操作的时间复杂度为 O(1)，适合需要高频插入/删除的场景。

---

### **示例代码**
```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};

    // 提取键为2的节点
    auto node = m.extract(2);
    if (!node.empty()) {
        node.key() = 4; // 修改键为4
        m.insert(std::move(node)); // 重新插入
    }

    // 输出结果：1:one, 3:three, 4:two
    for (const auto& [k, v] : m) {
        std::cout << k << ":" << v << " ";
    }
    return 0;
}
```

---

### **适用场景**
- 需要高效转移容器元素。
- 需要修改有序容器的键。
- 避免元素拷贝（如元素类型不可拷贝或拷贝代价高）。

`node_type` 提供了一种更灵活、高效的容器操作机制，是 C++17 中对关联容器的重要增强。