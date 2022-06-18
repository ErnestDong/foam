---
tags: CS, CSAPP, OS
---

# Synchronization

两个线程在某个时间点共同达到互相已知的状态

## 生产者消费者模型

生产者产生任务放入队列，消费者从队列取出资源执行。

### 条件变量 cv

 conditional variable

 把自旋变成睡眠，直到完成操作后唤醒。需要提供三个 API

- `wait(cv, mutex)`：释放掉 mutex 并且进入睡眠状态
- `signal/notify(cv)`：如果有线程在等 cv，就唤醒其中一个
- `broadcast/notifyall(cv)`：唤醒所有等待 cv 的线程

但是要注意，consumer 不能唤醒 consumer，需要设置两个条件变量

```c
// 需要等待条件满足时
mutex_lock(&mutex);
while(!cond){
    wait(&cv, &mutex);
}
assert(cond);
mutex_unlock(&mutex);

// 唤醒其他线程时，signal 可能唤醒错误的线程
broadcast(&cv);
```

### 信号量

限制在同一段序列中出现的线程数，接口为

- `P` 是判断可进入的线程数 token 是否大于0，大于0就 token-1 ，等于 0 就加入等待序列
- `V` 是释放 token ，让等待序列获得资源，或是使 token+1

```c
void producer{
    P(&empty); // 得到访问锁的权限
    printf("(");
    V(&fill);
}
void consumer{
    P(&fill);
    printf(")");
    V(&empty);
}
```

## leader/follower

分布式系统中常用，一个集中的 leader 集中管理资源来分配