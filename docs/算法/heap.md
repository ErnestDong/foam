---
tags: algorithm
---
# 堆

堆是一个数组，近似可以看作是一个二叉树。除最底层外，该数完全被充满，并且是从左向右填充。

## 快速计算

```python
def PARENT(i):
    return heap[i/2]
def LEFT(i):
    return heap[2*i] # 可以用i左移一位
def RIGHT(i):
    return heap[2*i + 1] # 可以用i右移一位
```

## 维护堆的性质

在程序每一步中，从 A[i] A[LEFT] A[RIGHT] 中选择最大值的下标 largest

-   如果 A[i] 最大，那么以 i 为根节点的子树已经是最大堆
-   否则交换 A[i] 和 A[largest]的值

## 建堆

单个元素是堆，不断重复上一步骤
## 堆排序

不断取出堆顶元素，并维护这个堆，直到取出所有元素 性能一般低于 [[快速排序]]
