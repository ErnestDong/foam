---
tags: cli
---
# TeX

$\TeX{}$ 是一种排版引擎，编程之后通过 $\TeX{}$ 编译出格式美观的文件（例如 pdf）。为了方便人们编写这样的程序，有很多宏集（即一些人编好了部分程序让我们方便地调用不用写负责的程序，著名的比如 $\LaTeX{}$

## 公式

TeX 可以很方便地插入公式，两个$之间是单行公式，或者可以用 equation 环境

[部分符号](https://www.math.pku.edu.cn/teachers/lidf/docs/textrick/symbols-a4.pdf)

[symbols](../../attachments/symbols.pdf)
注意某些符号在 [[TeX]]中有特殊含义，如%、&，使用前加一个反斜杠\。此外空白会被忽略，~可以代表一个空白字符，两个反斜杠可以是换行。

## 图片

### 语法

options can be h(ere) t(op) b(ottom)

## BibTeX

### biber return code with 2

delete the following folder

```shell
rm -rf (biber --cache)
```
