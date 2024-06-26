---
tags: Cpp
---

# STL

![stl](../../attachments/stl.png)

C++ 的标准模版库 STL 有 6 大类

- containers
- iterators
- algorithms
- adapters
- functors
- allocator

## 容器 containers

### sequence container

- vector：可变长数组
- stack：[[栈]]
- queue：[[队列]]
- deque：双端队列，分段连续，超过时增加 buffer
- array：数组包裹成 stl 的格式
- list：[[链表]]，每次需要增加内存的是两倍大小

### associative container

方便大量查找，包括 set/multiset（key-value 不分） map/multimap（key-value 查询），通常用[[红黑树]]实现

### unordered container

也是一种关联容器，是不定序的容器，[[哈希表]] 的链接法实现

## 分配器 allocators

不应该直接使用，因为不用容器和手动 malloc free 之外反而更复杂

[//begin]: # "Autogenerated link references for markdown compatibility"
[栈]: ../algorithm/data_structure/栈.md "栈"
[队列]: ../algorithm/data_structure/队列.md "队列"
[链表]: ../algorithm/data_structure/链表.md "链表"
[红黑树]: ../algorithm/data_structure/红黑树.md "红黑树"
[哈希表]: ../algorithm/data_structure/哈希表.md "哈希表"
[//end]: # "Autogenerated link references"
