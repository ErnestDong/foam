# 元编程

## 动态创建类

`type` 可以动态创建，需要声明继承自哪个类(空则继承自 object)，使用了哪些方法/类属性

```python
type(classname, (Father), {methods})
```

方法接受的参数必须有 self，self 绑定到本身

## 元类

对象由类创建，类及元类可以创建类

### `metaclass`

不使用 type 创建类，而是使用自定义的方法创建类，则在定义类时增加`metaclass=xxx`

其中的 xxx 可以定义想要的操作，接受 `classname, (Father), {methods}`，返回 `type` 创建的类
