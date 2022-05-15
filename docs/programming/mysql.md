---
tags: CS
---
# mysql

## Table

### 数据类型

表类似 excel 的一个 sheet

[[mysql]] 的数据形式有六种，分别是

-   INT:整数
-   DECIMAL(m,n): 总共有 m 位数，小数点后有 n 位
-   VARCHAR(n): n 位 string
-   BLOB: 二进制资料
-   DATES: \`YYYY-MM-DD\` 日期
-   TIMESTAMP: \`YYYY-MM-DD HH:MM:SS\`

```sql
CREATE TABLE student(
    studentID INT PRIMARY KEY,
    `name` VARCHAR(20),
    major VARCHAR(20)
);
DESCRIBE `student`; -- DESC是降序

ALTER TABLE student ADD gpa DECIMAL(3,2); -- ADD can be DROP
```

### 主键

`PRIMARY KEY` 可以不止一个

### 增删查改

1.  增

    ```sql
    INSERT INTO student VALUES(1, '董晨阳', 'RMI', 4.00);
    SELECT * FROM student;
    INSERT INTO student(studentID, `name`, major, gpa) VALUES(1, '晨阳', 'RMI', NULL);
    ```
    
    1.  加入限制
    
        ```sql
        CREATE TABLE student(
            studentID INT PRIMARY KEY,
            `name` VARCHAR(20) UNIQUE,
            major VARCHAR(20) NOT NULL,
            gpa DECIMAL(3,2) DEFAULT 4.00
        );
        ```
        
        其他如
        
        -   AUTO_{INCREMENT} 自动递增

2.  删

    ```sql
    DELETE FROM student WHERE gpa < 2.0
    ```

3.  查

    ```sql
    SELECT `name`, studentID FROM student WHERE gpa < 3.70 ORDER BY gpa, studentID DESC;
    ```
    
    可以加 `LIMIT 3` 来限制传回来的数量

4.  改

    ```sql
    UPDATE student SET major = "风险管理与保险", gpa = 4.00 WHERE major = "RMI" OR major IN("风保");
    ```

### 重命名 AS

```sql
SELECT studentID AS STDID from student
```

**\***

### 导入数据

以 csv 为例子

```sql
LOAD DATA INFILE filename
INTO TABLE tablename
FIELDS TERMINATED BY ","
LINES TERMINATED BY "\n"
```

## 数据库

一个数据库中可以有多个 [Table]

不同的 Table 以[1.3.2]链接

### 数据库的创建与删除

\\\`\\\`可以避免命名与关键字冲突

```sql
CREATE DATABASE `test`
SHOW DATABASES;
DROP DATABASE test;
USE test;
```

### 外键 foreign key

对应到某一张[Table]用 REFERENCES

```sql
CREATE TABLE scores(score INT PRIMARY KEY DEFAULT 0,
                    studentID INT UNIQUE,
                    FOREIGN KEY (studentID) REFERENCES student(studentID) ON DELETE SET NULL);
ALTER TABLE students ADD FOREIGN KEY(studentID) REFERENCES scores(studentID) ON DELETE CASCADE;
```

新增的时候外键不存在会报错，所以可以先写为 `NULL` 然后再修改

### 连接查询

1.  内连接

    1.  等值连接
    
        ```sql
        select e.name, d.name from emp e join dept d on e.deptnum = d.deptnum
        ```
    
    2.  非等值连接
    
    3.  自连接

2.  外连接

    1.  左连接
    
    2.  右连接

3.  全连接

## 数据处理

### AGGREGATE FUNCTIONS

有某个属性的资料有多少/平均 etc.

1.  COUNT

    ```sql
    SELECT COUNT(gpa) FROM student;
    ```

2.  AVG

    平均

3.  SUM

    总和

4.  MAX & MIN

### WILDCARDS

通配符

-   `%` 多个
-   `_` 一个

```sql
SELECT * FROM student WHERE major LIKE "%管理%";
```

### UNION

多个搜寻结果结合在一起

必须数据类型一样

```sql
SELECT score FROM scores UNION SELECT studentID from scores
```

### JOIN

连接多个表格

语法是 `something JOIN something ON condition`

### group by

group by 和 where 无法同时用，可以用 have

### SUBQUERY

类似[[shell]]里面的管道

用法是

```sql
SELECT username FROM users WHERE userid = (SELECT userid FROM sudoers);
```

### ON DELETE

从某一张表删除一条数据怎么办？

`ON DELETE SET NULL` 设为空

`ON DELETE CASCADE` 直接删掉

## 与 [[python]] 互动

### raw mysql

```python
import mysql.connector
# import sqlite
connection = mysql.connector.connect(host='localhost', port='3306', user='root', password='password', database='optional')
cursor = connection.cursor()
cursor.execute("SQL here")
records = cursor.fetchAll() # 取出回传资料
connection.commit() # 生效数据库修改
cursor.close()
connection.close()
```

### pandas

依赖[[mysql#ORM 模型]]

```python
import pandas as pd
from sqlalchemy import create_engine
engine = create_engine(
    'mysql+pymysql://root:password@localhost:3306/dbname')
sql = '''select * from employee'''
df = pd.read_sql(sql, engine)
```

### ORM 模型

所谓“对象-关系模型”，是把[[mysql#Table]]结构映射到对象上。

```python
# 导入:
from sqlalchemy import Column, String, create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base

# 创建对象的基类:
Base = declarative_base()

# 定义User对象:
class User(Base):
    # 表的名字:
    __tablename__ = 'user'

    # 表的结构:
    id = Column(String(20), primary_key=True)
    name = Column(String(20))

# 初始化数据库连接:
engine = create_engine('mysql+mysqlconnector://root:password@localhost:3306/test')
# 创建DBSession类型:
DBSession = sessionmaker(bind=engine)

# 创建session对象:
session = DBSession()
# 创建新User对象:
new_user = User(id='5', name='Bob')
# 添加到session:
session.add(new_user)
# 提交即保存到数据库:
session.commit()
# 关闭session:
session.close()
```

## Oracle SQL

-   LIMIT 1 变成了 WHERE ROWNUM < 1
-   HAVING 可以使用 WHERE 不用别的
## engine

处理表的处理器

| Engine                       | Support | Comment                                                        | Transactions | XA     | Savepoints |
|---------------------------- |------- |-------------------------------------------------------------- |------------ |------ |---------- |
| ARCHIVE                      | YES     | Archive storage engine                                         | NO           | NO     | NO         |
| BLACKHOLE                    | YES     | /dev/null storage engine (anything you write to it disappears) | NO           | NO     | NO         |
| MRG_{MYISAM}         | YES     | Collection of identical MyISAM tables                          | NO           | NO     | NO         |
| FEDERATED                    | NO      | Federated MySQL storage engine                                 | <null>       | <null> | <null>     |
| MyISAM                       | YES     | MyISAM storage engine                                          | NO           | NO     | NO         |
| PERFORMANCE_{SCHEMA} | YES     | Performance Schema                                             | NO           | NO     | NO         |
| InnoDB                       | DEFAULT | Supports transactions, row-level locking, and foreign keys     | YES          | YES    | YES        |
| MEMORY                       | YES     | Hash based, stored in memory, useful for temporary tables      | NO           | NO     | NO         |
| CSV                          | YES     | CSV storage engine                                             | NO           | NO     | NO         |
