# DeepSeek

> [DeepSeek - 探索未至之境](https://chat.deepseek.com/a/chat/s/34f54f95-40d4-426d-a73f-aded4e395a22)

常用的数据结构是计算机存储和组织数据的方式，选择合适的数据结构可以提高算法的效率。C++ 标准模板库（STL）提供了多种容器，这些容器就是对这些经典数据结构的具体实现。下面按类别介绍常用的数据结构及其在 C++ 中的对应。

### 1. 线性结构

- **数组（Array）**  
  静态数组：`std::array`（固定大小，C++11 引入）  
  动态数组：`std::vector`（可变大小，自动扩容）

- **链表（Linked List）**  
  单向链表：`std::forward_list`（C++11 引入）  
  双向链表：`std::list`

- **栈（Stack）**  
  `std::stack`（容器适配器，默认基于 `std::deque`）

- **队列（Queue）**  
  普通队列：`std::queue`（容器适配器，默认基于 `std::deque`）  
  双端队列：`std::deque`（可在头尾快速插入/删除）

- **字符串（String）**  
  `std::string`（本质是字符的动态数组，提供字符串专用操作）

### 2. 树形结构

- **二叉树（Binary Tree）**  
  C++ 标准库没有直接提供通用的二叉树容器，但可以通过指针或容器组合实现。

- **二叉搜索树（BST）**  
  有序集合/映射的底层通常用红黑树实现：  
  `std::set`（集合，元素唯一且有序）  
  `std::multiset`（允许重复元素的有序集合）  
  `std::map`（键值对映射，键唯一且有序）  
  `std::multimap`（允许重复键的有序映射）

- **堆（Heap）**  
  优先队列：`std::priority_queue`（容器适配器，默认基于 `std::vector`，提供最大堆）

- **并查集（Union-Find / Disjoint Set）**  
  标准库没有直接提供，需手动实现或用第三方库。

### 3. 散列结构

- **哈希表（Hash Table）**  
  无序集合/映射基于哈希表实现：  
  `std::unordered_set`（C++11 引入）  
  `std::unordered_multiset`  
  `std::unordered_map`  
  `std::unordered_multimap`

### 4. 图形结构

- **图（Graph）**  
  标准库没有专门的图容器，通常用邻接表（`std::vector<std::list<int>>` 或 `std::unordered_map`）或邻接矩阵（`std::vector<std::vector<bool>>`）表示。

### 5. 其他常用数据结构

- **位集（Bitset）**  
  `std::bitset`（固定大小的二进制位容器，支持位运算）

- **元组（Tuple）**  
  `std::tuple`（C++11 引入，可存储不同类型元素的固定大小集合）

- **可选值（Optional）**  
  `std::optional`（C++17 引入，表示可能存在或不存在的值）

### 总结

C++ STL 提供了丰富的容器，涵盖了大部分常用数据结构。使用时需要根据具体需求（如有序性、唯一性、查找速度、内存布局等）选择合适的容器。对于 STL 未直接支持的结构（如图、并查集），可以基于现有容器或自定义数据结构实现。
