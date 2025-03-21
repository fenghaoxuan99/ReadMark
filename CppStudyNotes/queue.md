
![](..\Image\queue.png)

![](..\Image\queue.jpeg)
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->
<!-- code_chunk_output -->
- [queue 容器的基本概念](#queue-容器的基本概念)
  - [queue 容器的基本概念](#queue-容器的基本概念)
  - [queue 容器的基本操作](#queue-容器的基本操作)
      - [std::queue<T,Container>::emplace](#stdqueuetcontaineremplace)
- [std::priority_queue](#stdpriority_queue)

<!-- /code_chunk_output -->

## queue 容器的基本概念
```cpp
template<
    class T,
    class Container = std::deque<T>
> class queue;
```
**std::queue 类模板是 容器适配器，它提供了 队列 的功能 - 具体来说，是一种 FIFO（先进先出）数据结构。**

- 概念：queue是一种先进先出(First In First Out,FIFO)的数据结构，队列容器允许从一端插入元素，从另一端移除元素。
- 说明：
通常队头为移除数据，队尾插入数据；
队列没有迭代器的操作，因为无法遍历数据，只能在队头和队尾操作数据；
![d](..\Image\\queue.jpeg)

## queue 容器的基本操作
|函数原型|功能|
|:--:|:--:|
|size()	            |返回容器中元素的个数|
|empty()	        |判断容器是否为空|
|resize(num)	    |重新指定容器的长度为num，若容器变长，填充 0；如果容器变短，则末尾超出容器长度的元素被删除|
|resize(num, elem)	|重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。|
|push(elem)         |向队尾插入元素|
|pop()	            |移除队头元素|
|back()	            |获取队尾元素|
|front()	        |获取队头元素|


#### std::queue<T,Container>::emplace

```cpp
template< class... Args >
void emplace( Args&&... args );

template< class... Args >
decltype(auto) emplace( Args&&... args );
```
将新元素推到队列的末尾。元素被就地构造，即不执行复制或移动操作。


# std::priority_queue
```cpp
template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> class priority_queue;
```
优先级队列是优先级队列是一种容器适配器，它提供常数时间的最大（默认情况下）元素查找，但插入和提取操作的时间复杂度为对数。




`std::priority_queue` 是 C++ 标准库中的一个容器适配器（Container Adapter），它基于堆（Heap）数据结构实现，默认情况下提供最大堆（Max-Heap）的特性，即队列顶部（`top()`）始终是当前最大的元素。
它常用于需要按优先级处理元素的场景（如任务调度、图算法中的最短路径等）。

---

### **基本特性**
- **默认行为**：最大堆（顶部元素最大）。
- **底层容器**：默认使用 `std::vector`，但可以指定其他支持随机访问迭代器和特定操作的容器（如 `std::deque`）。
- **时间复杂度**：
  - 插入元素（`push`）：O(log n)
  - 删除顶部元素（`pop`）：O(log n)
  - 访问顶部元素（`top`）：O(1)
- **不支持直接遍历**：只能访问顶部元素，不能随机访问其他元素。

---

### **构造函数**
`std::priority_queue` 提供多种构造函数，允许自定义底层容器和比较规则。

#### 1. **默认构造函数**
创建一个空的优先级队列，使用默认底层容器（`std::vector`）和默认比较规则（`std::less<T>`，即最大堆）。
```cpp
std::priority_queue<int> pq; // 默认最大堆
```

#### 2. **指定底层容器和比较规则**
可以显式指定底层容器和比较函数：
```cpp
#include <queue>
#include <vector>
#include <functional>

// 使用 vector 作为底层容器，最小堆（通过 greater<int>）
std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
```

#### 3. **通过迭代器初始化**
通过已有数据范围初始化：
```cpp
std::vector<int> data = {3, 1, 4, 1, 5};
std::priority_queue<int> pq(data.begin(), data.end()); // 最大堆
```

#### 4. **拷贝构造**
从另一个 `priority_queue` 拷贝构造：
```cpp
std::priority_queue<int> pq1;
pq1.push(10);
std::priority_queue<int> pq2(pq1); // 拷贝构造
```

---

### **成员函数**
#### 1. **元素操作**
- `void push(const T& value)`：插入元素。
- `template <class... Args> void emplace(Args&&... args)`：原地构造元素（避免拷贝）。
- `void pop()`：删除顶部元素（不返回被删除的元素）。
- `const T& top() const`：返回顶部元素的常量引用（不可修改）。

#### 2. **容量查询**
- `bool empty() const`：判断队列是否为空。
- `size_type size() const`：返回元素数量。

---

### **底层容器与自定义比较规则**
#### 1. **底层容器**
默认使用 `std::vector`，但可以替换为支持以下操作的容器：
- `front()`：访问第一个元素。
- `push_back()`：尾部插入元素。
- `pop_back()`：尾部删除元素。
- 随机访问迭代器（用于堆操作）。

例如，使用 `std::deque`：
```cpp
std::priority_queue<int, std::deque<int>> pq;
```

#### 2. **自定义比较规则**
通过模板参数指定比较函数，实现最小堆或其他优先级逻辑：
```cpp
// 最小堆
std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;

// 自定义比较函数（例如按字符串长度排序）
struct CompareStringLength {
    bool operator()(const std::string& a, const std::string& b) {
        return a.length() < b.length(); // 长度大的优先级高
    }
};

std::priority_queue<std::string, std::vector<std::string>, CompareStringLength> custom_pq;
```

---

### **性能分析**
- **插入（`push`）**：O(log n)，需要维护堆结构。
- **删除（`pop`）**：O(log n），需要重新调整堆。
- **访问顶部（`top`）**：O(1)，直接返回堆顶元素。
- **底层容器选择**：
  - `std::vector`：内存连续，缓存友好，适合大多数场景。
  - `std::deque`：支持头尾高效插入，但内存不连续，可能略微降低性能。

---

### **应用场景**
1. **任务调度**：按优先级处理任务。
2. **Top K 问题**：快速找到数据流中最大的 K 个元素。
3. **图算法**：如 Dijkstra 算法中按距离优先处理节点。
4. **合并有序序列**：多路归并时选择当前最小的元素。

---

### **与其他容器的对比**
| 特性                | `priority_queue`       | `std::set`/`std::multiset`    | `std::vector` + `std::sort` |
|---------------------|------------------------|-------------------------------|-----------------------------|
| **元素有序性**      | 堆结构（部分有序）     | 完全有序（红黑树）            | 完全有序（需显式排序）      |
| **插入/删除效率**   | O(log n)               | O(log n)                      | O(n)（插入中间）            |
| **访问顶部元素**    | O(1)                  | O(1)（通过 `begin()`）        | O(1)（通过 `back()`）       |
| **内存连续性**      | 连续（`vector` 底层）  | 非连续（红黑树节点）          | 连续                        |

---

### **示例代码**
#### 1. 最小堆实现
```cpp
#include <queue>
#include <iostream>

int main() {
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
    min_pq.push(3);
    min_pq.push(1);
    min_pq.push(4);

    while (!min_pq.empty()) {
        std::cout << min_pq.top() << " "; // 输出：1 3 4
        min_pq.pop();
    }
    return 0;
}
```

#### 2. 自定义比较规则
```cpp
#include <queue>
#include <string>

struct CompareByLength {
    bool operator()(const std::string& a, const std::string& b) {
        return a.length() < b.length(); // 长度长的优先级高
    }
};

int main() {
    std::priority_queue<
        std::string,
        std::vector<std::string>,
        CompareByLength
    > pq;

    pq.push("apple");
    pq.push("banana");
    pq.push("cherry");

    std::cout << pq.top(); // 输出 "banana"（长度6）
    return 0;
}
```

---

### **注意事项**
1. **不可直接修改元素**：通过 `top()` 返回的是 `const` 引用，修改元素会破坏堆结构。
2. **底层容器限制**：不能直接访问底层容器（除非通过继承或特定实现）。
3. **比较函数一致性**：自定义比较规则需严格遵循堆的数学性质（如传递性）。

`std::priority_queue` 是处理优先级问题的利器，尤其适合需要高效插入和删除顶部元素的场景。
