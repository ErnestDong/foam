---
tags: python
---
# python

## [[函数式编程]]

### 偏函数

偏函数作用就是，把一个函数的某些参数给固定住（也就是设置默认值），返回一个新的函数，调用这个新函数会更简单。

```python
>>> import functools
>>> int2 = functools.partial(int, base=2)
>>> int2('1000000')
64
>>> int2('1010101')
85
```

### 装饰器

#### dataclass

it will make the class comparable, (imuttable, hashable)

```python
from dataclasses import dataclass, field
@dataclass(frozen=True)
class Comment:
    id: int = field()
    text: str = field(default="")
```

## 面向对象

### `@property`

Python 内置的 `@property` 装饰器就是负责把一个方法变成属性调用的。把一个 `getter` 方法变成属性，只需要加上 `@property` 就可以了

`@property` 本身又创建了另一个装饰器 `@(under property function).setter`，负责把一个 `setter` 方法变成属性赋值

### 抽象类

要继承自 abc.ABC，抽象方法使用@abstractmethod装饰器 标记，而且定义体中通常只有文档字符串。即使实现了相应的方法也需要在子类重写，尽管可以 `super.__init__()`

### 多继承

如果两个父类方法有冲突，优先使用前面的父类方法

## GC

函数内循环引用，函数结束后无法释放内存

### 手动清除

```python
import gc
def recur():
    a = [i for i in range(100_0000_0000)]
    b = [i for i in range(100_0000_0000)]
    a.append(b)
    b.append(a)

recur()

gc.collect()
```

### 机制

引用计数为主，分代收集为辅

## 上下文管理器

避免 IO 过程中出现错误没有释放资源

### 类的方法实现

只要实现了 `__enter__` 和 `__exit__` 方法，就可以用 `with` 来管理

### 方法实现

`@contextmanager` 这个 decorator 接受一个 generator，用 yield 语句把 with &#x2026; as var 把变量输出出去，然后，with 语句就可以正常地工作了：

```python
from contextlib import contextmanager

@contextmanager
def my_open(path, mode):
    f = open(path, mode)
    """__enter__"""
    yield f
    """__exit__"""
    f.close()
with my_open("file","w") as f:
    f.write(123)
```

## build system

poetry can do the best as far as I can see

```shell
poetry new project
poetry init
poetry add package
poetry install
poetry build    # 构建可安装的 *.whl 和 tar.gz 文件
poetry shell    # 会根据定义在 pyproject.toml 文件中的依赖创建并使用虚拟环境
poetry run pytest    # 运行使用 pytest 的测试用例，如 tests/test_sample.py
poetry run python -m unittest tests/sample_tests.py  # 运行 unittest 测试用例
poetry export --without-hashes --output requirements.txt  # 导出 requirements.txt 文件, --dev  导出含 dev 的依赖，或者用 poetry export --without-hashes > requirements.txt
poetry run my-script
```

poetry generates pyproject.toml

```toml
[tool.poetry.scripts]
my-script="modulename.filename:function_name"
```
