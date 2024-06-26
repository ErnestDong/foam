---
tags: python
---

# pandas

pandas 封装了 [[numpy]] 的一些操作，使得 [[python]] 可以像操作 excel （其实是基于 R 的语法）一样操作数据（称为 [3.1.2]）

中文文档：<https://www.pypandas.cn/docs/getting_started/10min.html> 英文文档：<https://pandas.pydata.org/docs/>

## 对象

### `Series`

可以理解成一列 excel 数据

### `DataFrame`

可以理解成一张 excel 表，可以用切片/属性的方式访问某一列

```python
dates = pd.date_range('20130101', periods=6)
df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list('ABCD'))
print(df.columns)
print("===")
print(df)
print("===")
print(df.T)
print("===")
print(df.A)
```

1. dataframe 的导入导出

   导入可以用 `pd.read_*` ，而导出可以用 `pd.to_*` ，如 csv, excel

2. 查看数据

   df 有属性 `head(n)`, `tail(n)` 可以查看头/尾 n 条数据

   `describe()` 可以快速查看数据的统计摘要：

   ```python
   desc = df.describe()
   print(desc)
   print(desc['A'])

   ```

3. 切片

   一个 [] 切出来是一个 Series，两个[[]] 则是 dataframe

   ```python
   df["A"] # return the column A as Series
   df[["A", "B"]] # return column AB as a new df
   ```

4. 排序

   ```python
   print(df.sort_values(by = ['A', 'B'], ascending=False))
   ```

5. 筛选

   向量化操作会更快，条件中间用&

   ```python
   print(df[df["A"]<0])
   ```

6. 运算

   运算基本类似 numpy ，但是没有广播机制，必须对齐

   特别的，有 `apply` 函数很常用

   `df.apply(lambda x: x.max() - x.min())`

   `apply` 的含义是，对每一个 Series ，应用这个函数，并返回结果

7. 合并

   两个 dataframe 合并，操作中 how 必须是 One of [left,right,outer,inner]. Defaults to inner.

   ```python
   left = pd.DataFrame({'key': ['foo', 'bar'], 'lval': [1, 2]})
   right = pd.DataFrame({'key': ['foo', 'bar', "etc"], 'rval': [4, 5, 6]})

   print(pd.merge(left, right, on="key", how="left"))
   ```

8. `group_by`

   return (group, df*{in}*{group})

   ```python
   df = pd.DataFrame(
       {
           "A": ["foo", "bar", "foo", "bar", "foo", "bar", "foo", "foo"],
           "B": ["one", "one", "two", "three", "two", "two", "one", "three"],
           "C": np.random.randn(8),
           "D": np.random.randn(8),
       }
   )
   print(df.groupby("A").sum())
   ```

## 其他

### `dropna`

`df.dropna()` 删除掉空值

### `cut`

```python
df = pd.DataFrame({0:[i for i in range(100)]})
cutted = pd.cut(df[0], bins=[-1, 50, 101])
print(cutted)
```

### `value_counts`

```python
print(cutted.value_counts())
```

### 透视表

1. `pivot_table`

   有三个最重要的参数 index、values、aggfunc

   1. index

      针对不同的索引构建透视表

      ```python
      pd.pivot_table(df,index=['a', 'b'])
      ```

   2. values

      values 可以对需要的计算数据进行筛选

   3. aggfunc

      aggfunc 参数可以设置我们对数据聚合时进行的函数操作，默认是 mean

2. `pivot`

   仅仅是用来 reshape dataframe

   ```python
   df.pivot(index="row as", columns="column as", value="show what value")
   ```

3. `melt`

   将二维的表转换成关系型数据库的格式，下面的代码保留了 keep 将 melt\* 变成了一列

   ```python
   pd.melt(df, id_vars=['keep'], value_vars=['melt1', 'melt2'])
   ```

### `stack`

将一个 multiIndex 的多列变成一个更加 multiIndex 的一列

`unstack` 是相反的过程

[//begin]: # "Autogenerated link references for markdown compatibility"
[numpy]: numpy.md "numpy"
[python]: ../python.md "python"
[//end]: # "Autogenerated link references"
