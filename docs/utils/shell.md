---
tags: cli
---
# shell

## header/shebang

```shell
\#! /bin/bash
```

## variable

use $ to call the variable

no space around =

UPPERCASE by convention

定义时候不用 dollar ，调用时候需要

双引号会转义，单引号不会

### input

```shell
read -p "Enter your name" NAME
```

### operator

| -gt        | &gt;           |
| -and so on | \\\\ and so on |

### read only

不可以 unset 删除和修改

### 字符串操作

\\# 取长度，如 `#email` 为该变量长度

`\dollar{str1:start:length}` 取截取字符串

### test

类似于 `assert` 。

## IF and CASE

```shell
NAME="dcy"
if [ "$NAME" == "dcy" ]
   then
       echo "Hello $NAME"
   else
       echo "who are you"
fi
```

## FOR and WHILE

```sh
for NAME in $NAMES
do
    echo "$NAME"
done

num = 1
while((num <=5))
do
    num += 1
done
```

## function
