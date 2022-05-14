---
tags: python
---
# [[python]] 实用模块

## `collections`

### `Counter`

是 dict 的子类，可以用来对 hashable 对象计数

### `abc`

抽象基类

### TODO `default dict`

## `logging`

### example

```python
import logging

logger = logging.getLogger(__name__)

stream_hdl = logging.StreamHandler()
file_hdl = logging.FileHandler("filename.log")

stream_hdl.setLevel(Logging.warning)
file_hdl.setLevel(logging.info)

formatter = logging.format("%(name)s - %(levelname)s - %(message)s")
stream_hdl.setFormatter(formatter)
file_hdl.setFormatter(formatter)

logger.addHandler(stream_hdl)
logger.addHandler(file_hdl)
```

### lazy logging

```python
logging.info("now %s is lazy", string_you_like)
```

## `hashlib`

### example

```python
import hashlib

data = "hello"

md5 = hashlib.md5(data.encode())
result = md5.hexdigest()
```

## [[单元测试]]

## [[爬虫]]

## [[神经网络]]
