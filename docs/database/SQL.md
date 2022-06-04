---
tags: CS
---
# 关系型数据库

## 存储对象

### 视图

虚拟存在的表，只保存了 [[SQL]] 的逻辑，不保存数据

```sql
CREATE OR REPLACE VIEW myview AS SELECT * FROM backtest;
```

### 存储过程

封装 SQL 语句进行重用

```sql
CREATE PROCEDURE p1(IN score INT, OUT res VARCHAR(10))
    BEGIN
        IF score >= 85 THEN
            SET res := "good";
        ELSE
            SET res := "bad";
        END IF;
    END;
CALL p1();
```

#### 存储函数

```sql
CREATE FUNCTION func(n INT)
RETURNS INT
BEGIN
    DECLARE TOTAL INT DEFAULT 0;
    WHILE n > 0 DO
          SET TOTAL := TOTAL + n;
          SET n := n + 1;
    END WHILE;
    RETURN TOTAL;
END;
```

### 触发器

是 INSERT/UPDATE/DELETE 的 hook ，确保数据的完整性、日志记录、数据校验

### 锁

- 全局锁
- 表级锁
- 行级锁

## 索引

sql 优化很多是依靠索引

### 索引结构

#### [[红黑树#B+ 树]]

一种特殊的[[红黑树#B 树]]

区别在

- 所有元素出现在叶子节点上，非叶子节点虽然有值但只是索引的作用，不存储数据
- 所有叶子节点形成了一个单向 [[数据结构#链表]]

在 [[Mysql]] 中优化成双向循环链表，利于数据排序

#### [[哈希表]]

性能高，但只能精确匹配，不支持范围匹配， [[mysql]]中只有 memory 引擎支持

#### R-tree

空间索引，地理位置适合， [[mysql]]只有 MyISAM 引擎支持

#### Full-text

全文索引，类似 elastic search

### 索引分类

#### 通常分类

1. 主键索引

    只能有一个 PRIMARY

2. 唯一索引

    可以有多个 UNIQUE

3. 常规索引

4. 全文索引

#### [[Mysql]] 分类

- cluster index：有且只有一个且必须有，无论如何至少会存在一个隐藏的 row num 索引，下面挂着行数据
- secondary index：下面挂着 cluster 数据

### 作用

对某列

```sql
CREATE INDEX idx ON backtest(TRADE_DT)
```

创建索引后，SELECT 、 ORDER BY 等会快很多

但如果用联合索引，最左边的列没有出现，索引不会生效。如果跳过某一列，后面的列失效

## 关系

### 关系的定义

$Relation=R(U,D,DOM,F)$ ，描述了关系包括哪些属性、属性来自哪些域、域和属性的关系，以及属性间的依赖关系

### 关系代数

抽象的查询语言，用对关系的运算表达查询，要素为：运算对象（关系）、运算符（集合运算符与关系运算符）、和运算结果

#### 关系代数运算

集合运算符 $\cup,-,\cap,\times$ 并、差、交、笛卡尔积

关系运算符 $\sigma,\Pi,\Join,\div$ 选择、投影、连接、除

选择：包括比较 $\gt,\ge,\lt,\le,\eq,\le\gt$ 和逻辑与或非 $\land, \lor, \neg$

投影：对查询结果只留下某个或某几个属性

除：保留 R 中满足 S 的，但是要去掉 S 的列

#### 关系的完整性

1. 实体完整性：主码唯一且完全
2. 参照完整性：外码要么为空，要么对应另一表的主码
3. 用户定义完整性

### [[SQL]]

包括数据定义语言 DDL 、数据查询语言 DQL ，数据操纵语言 DML 以及数据控制语言 DCL
