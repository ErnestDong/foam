---
tags: Database
---
# 关系模型

## 概念

- schema 是使用给定数据模型对特定数据集合的描述。
- relation 是一个 **无序集合**，它包含表示实体的属性之间的关系。具有 n 个属性的 relation 称为 n 元 relation。
- tuple 是关系中的一组属性值(也称为其属性域)，在二维表里，元组也称为 row。
- 关系的主键唯一标识单个元组
- 外键指定一个关系中的属性必须映射到另一个关系中的元组

关系数据模型定义了三个概念

- Structure: 关系的定义及其内容
- Integrity: 确保数据库的内容满足约束条件。
- Manipulation: 如何访问和修改数据库的内容。

## 关系代数

关系代数是一种过程式的语言

### select

$\sigma_{predicate}(R)$ 代表输入一个关系，并从该关系中输出满足 predicate 元组的子集。predicate 起到了过滤器的作用，可以使用合取和析取来组合多个谓词。
在行上做选择，结果产生同类元素

> 合取 $p\bigvee q$ 为取`与`，并取 $p\bigwedge q$ 为取`或`

### Projection 投影

$\pi_{A_i}(R)$ 接受一个关系，并输出一个只包含指定属性的元组的关系。
在列上做选择，结果产生不同类元素

### Union

$(R\cup S)$ 接受两个关系并输出一个关系，该关系包含出现在至少一个输入关系中的所有元组。这两个输入关系必须具有完全相同的属性。

### Intersection

$(R\cap S)$ 接受两个关系，并输出一个包含这两个输入关系中出现的所有元组的关系。两个输入关系必须具有完全相同的属性

### Differernce

$(R-S)$ 接受两个关系并输出一个关系，该关系包含出现在第一个关系中但不包含第二个关系中的所有元组。注意：两个输入关系必须具有完全相同的属性

### Product

$(R\times S)$ 接受两个关系并输出一个关系，该关系包含来自输入关系的元组的所有可能组合

### Join

$R\Join S$ 接受两个关系并输出一个包含由两个元组组合而成的所有元组的关系，其中对于两个关系共享的每个属性，两个元组的该属性的值是相同的。

## 三大范式

- 第一范式：原子性，字段不可再拆
- 第二范式：在满足第一范式的基础上，非主键完全依赖主键(而不仅是主键的一部分)
- 第三范式：第二范式基础上，除了主键的字段必须直接依赖于主键