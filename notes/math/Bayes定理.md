---
tags: math
---

# Bayes 定理

## 定理形式

$$P{ \left( {\mathop{{B}}\nolimits_{{k}} \left| A\right. } \right) }=\frac{{P \left( {\mathop{{B}}\nolimits_{{k}}} \left)  \cdot P{ \left( {A \left| {\mathop{{B}}\nolimits_{{k}}}\right. } \right) }\right. \right. }}{{\mathop{ \sum }\limits_{{i=1}}^{{n}}P{ \left( {\mathop{{B}}\nolimits_{{i}}} \right) } \cdot P{ \left( {A \left| \mathop{{B}}\nolimits_{{i}}\right. } \right) }}}$$

## Bayes 估计

### 先验分布 后验分布

$P(A|B)=P(B|A)P(A)/P(B)$在形式上也可以表述为：

A 的后验概率 = (A 的似然度 \* A 的先验概率)/标准化常量，后验概率与先验概率和似然度的乘积成正比。

### 贝叶斯估计

待估计参数$\theta$也是随机的，和一般随机变量没有本质区别，因此只能根据观测样本估计参数$\theta$的分布。

$$
\pi(\theta|x)=\frac{f(x|\theta)\pi(\theta)}{\int f(x|\theta)\pi(\theta)\mathrm{d}\theta}
$$

其中$\pi(\theta)$为参数$\theta$的先验分布，表示对参数$theta$的主观认识，是非样本信息，$\pi(\theta|x)$ 为参数$\theta$的后验分布，分母$m(x)$与$\theta$无关

- 先求模型分布
- 再求联合分布
- 再求边际分布
- 除一下得到后验分布/计算预测分布
