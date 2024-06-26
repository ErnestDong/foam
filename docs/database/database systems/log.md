---
tags: Database
---

# logging

## undo log

实现了[[transaction]]中的原子性，主要用于事务回滚和[[MVCC]]，undo log 会写入 [[buffer_pools]] 中的 Undo Page。

每当 InnoDB 引擎对一条记录进行操作（修改、删除、新增）时，要把回滚时需要的信息都记录到 undo log 里，比如：

- 在**插入**一条记录时，要把这条记录的主键值记下来，这样之后回滚时只需要把这个主键值对应的记录**删掉**就好了；
- 在**删除**一条记录时，要把这条记录中的内容都记下来，这样之后回滚时再把由这些内容组成的记录**插入**到表中就好了；
- 在**更新**一条记录时，要把被更新的列的旧值记下来，这样之后回滚时再把这些列**更新为旧值**就好了。

## redo log

实现了[[transaction]]中的持久性，主要用于掉电等故障恢复；

为了防止断电导致数据丢失的问题，当有一条记录需要更新的时候，InnoDB 引擎就会先把记录写到 redo log 里面，并更新内存，这个时候更新就算完成了。
同时，InnoDB 引擎会在适当的时候，由后台线程将缓存在 Buffer Pool 的脏页刷新到磁盘里。
这就是 WAL （Write-Ahead Logging）技术，指的是 [[RDBMS]] 的写操作并不是立刻更新到磁盘上，而是先记录在日志上，然后在合适的时间再更新到磁盘上。

在事务提交时，只要先将 redo log 持久化到磁盘即可，可以不需要将缓存在 Buffer Pool 里的脏页数据持久化到磁盘。

## bin log

是 Server 层生成的日志，主要用于数据备份和主从复制；
记录了所有数据库表结构变更和表数据修改的日志，记录 MySQL 上的所有变化并以二进制形式保存在磁盘上。
