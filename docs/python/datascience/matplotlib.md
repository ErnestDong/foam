---
tags: python
---

# matplotlib

<https://matplotlib.org/stable/tutorials/index>

[[python]]基础的作图，对标 Matlab

## 中文

```python
plt.rcParams['font.sans-serif']=['SimHei'] #用来正常显示中文标签
plt.rcParams['axes.unicode_minus']=False
```

## example

pyplot 是 matplotlib 暴露给我们的接口，可以用 plt.plot 作图

教程：<https://matplotlib.org/stable/tutorials/introductory/pyplot.html>

```python
import matplotlib.pyplot as plt
import numpy as np
x = np.linspace(-5,5,100)
y = np.sin(x)
plt.plot(x,y)
filename="plts/example.png"
plt.title("example")
plt.xlabel("X")
plt.savefig(filename)

```

## 具体

| 折线图 | 直方图 | 散点图 | 饼图 |
| plot | bar | scatter | pie |

[//begin]: # "Autogenerated link references for markdown compatibility"
[python]: ../python.md "python"
[//end]: # "Autogenerated link references"